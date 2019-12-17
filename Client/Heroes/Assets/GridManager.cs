using System.Collections.Generic;
using System.Linq;
using UnityEngine;

namespace Heroes {
	public class GridManager : MonoBehaviour {
		public enum CellType {
			Ground, NotGround
			// Water, Props...
		}

		[System.Serializable]
		public class Cell {
			public Vector3 pos;
			public CellType type;

			public Cell(Vector3 pos, CellType type) {
				this.pos = pos;
				this.type = type;
			}
		}
		
		private class Node {
			public int no;
			public float f;
			public float g;
		}

		private Cell[] world;
		private Transform bottomLeft;
		private Transform topRight;
		private int row;
		private int col;

		[SerializeField] private float cellSize = 1.0f;

		private void Start() {
			bottomLeft = transform.Find("BottomLeft");
			topRight = transform.Find("TopRight");

			buildWorld();
		}
		
		public Vector3 cellToPos(int cellno) {
			if (cellno < 0 || cellno >= row * col) return Vector3.zero;

			return world[cellno].pos;
		}

		public int posToCell(Vector3 pos) {
			Vector3 diff = pos - bottomLeft.position;
			return Mathf.RoundToInt(diff.z / cellSize) * col + Mathf.RoundToInt(diff.x / cellSize);
		}

		public Vector3 posToCenter(Vector3 pos) {
			return cellToPos(posToCell(pos));
		}
		
		public void buildWorld() {
			Vector3 diff = topRight.position - bottomLeft.position;
			row = Mathf.CeilToInt(Mathf.Abs(diff.z) / cellSize);
			col = Mathf.CeilToInt(Mathf.Abs(diff.x) / cellSize);

			int maxCells = row * col;
			world = new Cell[maxCells];

			int layerMask = (1 << LayerMask.NameToLayer("Enviroment"))
				| (1 << LayerMask.NameToLayer("Water"));

			for (int i = 0; i < maxCells; ++i) {
				Vector3 worldPos = bottomLeft.position + new Vector3(i % col, 0, i / col) * cellSize;
				worldPos.y += cellSize;
				bool isGround = !Physics.CheckSphere(worldPos, cellSize, layerMask);
				CellType type = isGround ? CellType.Ground : CellType.NotGround;
				world[i] = new Cell(worldPos, type);
			}
		}

		//private void OnDrawGizmos() {
		//	if (world == null) return;

		//	foreach(var cell in world) {
		//		Gizmos.color = cell.type == CellType.Ground ? Color.white : Color.red;
		//		Gizmos.DrawCube(cell.pos, Vector3.one * cellSize);
		//	}
		//}

		private int[] findNeighbors(int cellno) {
			List<int> neighbors = new List<int> { -1, 1, -col, col, -col - 1, -col + 1, col - 1, col + 1 };

			if (cellno % col == 0) neighbors.RemoveAll((no) => { return no == -1 || no == -1 - col || no == -1 + col; });
			if (cellno % col == col - 1) neighbors.RemoveAll((no) => { return no == 1 || no == 1 - col || no == 1 + col; });
			if (cellno / col == 0) neighbors.RemoveAll((no) => { return no == -col || no == -col - 1 || no == -col + 1; });
			if (cellno / col == row - 1) neighbors.RemoveAll((no) => { return no == col || no == col - 1 || no == col + 1; });

			for (int i = 0; i < neighbors.Count;) {
				neighbors[i] += cellno;
				if (neighbors[i] < 0 || neighbors[i] >= row * col || world[neighbors[i]].type == CellType.NotGround) neighbors.RemoveAt(i);
				else ++i; /* increase unless removing */
			}

			// remove crossing-neighbors if they are blocked by two adjacent walls. See ppt page 41.
			Vector3 X = cellToPos(cellno);
			for (int i = 0; i < neighbors.Count;) {
				Vector3 Xp = cellToPos(neighbors[i]);

				if ((X.x - Xp.x) * (X.z - Xp.z) != 0) {
					if (world[posToCell(new Vector3(Xp.x, 0, X.z))].type == CellType.NotGround
						&& world[posToCell(new Vector3(X.x, 0, Xp.z))].type == CellType.NotGround) {
						neighbors.RemoveAt(i);
						continue;
					}
				}
				++i;
			}

			return neighbors.ToArray();
		}

		private int[] buildPath(int[] parents, int from, int to) {
			if (parents == null) return null;

			List<int> path = new List<int>();
			int current = to;
			while (current != from) {
				path.Add(current);
				current = parents[current];
			}
			path.Add(from); // to -> ... -> ... -> from
			path.Reverse(); // from -> ... -> ... -> to

			return path.ToArray();
		}

		private float computeDistance(int cell1, int cell2) {
			return Vector3.Distance(cellToPos(cell1), cellToPos(cell2));
		}

		private int[] findAstarPath(int from, int to) {
			int maxCells = row * col;

			if (from < 0 || from >= maxCells || to < 0 || to >= maxCells) return null;

			// initialize the parents of all tiles to negative value, implying no tile number associated.
			int[] parents = Enumerable.Repeat<int>(-1, maxCells).ToArray<int>();

			List<Node> closed = new List<Node>();
			List<Node> open = new List<Node>() { new Node { no = from, f = 0f, g = 0f } };
			while (open.Count > 0) {
				var lowScore = open.Min(node => node.f);
				var current = open.First(n => n.f == lowScore);
				open.Remove(current);
				closed.Add(current);

				int[] neighbors = findNeighbors(current.no);
				foreach (var neighbor in neighbors) {
					if (neighbor == to) {
						// found the destination
						parents[neighbor] = current.no;
						return buildPath(parents, from, to); // read parents array and construct the shoretest path by traversal
					}

					if (closed.FirstOrDefault(n => n.no == neighbor) != null) continue;

					var g = current.g + computeDistance(current.no, neighbor);
					var h = computeDistance(neighbor, to);
					var nodeInOpen = open.FirstOrDefault(n => n.no == neighbor);
					if (nodeInOpen == null) {
						parents[neighbor] = current.no;

						open.Insert(0, new Node { no = neighbor, f = g + h, g = g });
						continue;
					}
					if (g + h < nodeInOpen.f) {
						nodeInOpen.f = g + h;
						nodeInOpen.g = g;
						parents[neighbor] = current.no;
					}
				}
			}

			return null;        
		}

		public List<Vector3> findPath(Vector3 startPoint, Vector3 endPoint) {
			int start = posToCell(startPoint);
			int end = posToCell(endPoint);

			int[] route = findAstarPath(start, end);
			if (route == null) return null;

			List<Vector3> newPath = new List<Vector3>();
			foreach(var node in route) {
				newPath.Add(cellToPos(node));
			}

			return newPath;
		}
	}
}