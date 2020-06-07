using System.Linq;
using System.Collections.Generic;
using System.Threading.Tasks;
using UnityEngine;

namespace Heroes {
	public class GridManager : MonoBehaviour {
		private int row;
		private int col;
		private float cellSize;
		private Cell[] world;

		private class Node {
			public int no;
			public float f;
			public float g;
		}

		private void Awake() {
			ObjectManager.Instance.DontDestroyOnLoad(this.gameObject);	
		}

		public async Task loadWorldMap() {
			var jsonData = await Util.AsyncLoadJsonFile("/Data", "world_map");
			WorldMapData worldMap = JsonUtility.FromJson<WorldMapData>(jsonData);
			this.row = worldMap.row;
			this.col = worldMap.column;
			this.cellSize = worldMap.cellSize;
			this.world = worldMap.map;
		}

		public Vector3 cellToPos(int cellno) {
			if (cellno < 0 || cellno >= row * col) {
				return Vector3.zero;
			}

			return world[cellno].position;
		}

		public int posToCell(Vector3 pos) {
			Vector3 diff = pos - world[0].position;
			return Mathf.RoundToInt(diff.z / cellSize) * col + Mathf.RoundToInt(diff.x / cellSize);
		}

		public Vector3 posToCenter(Vector3 pos) {
			return cellToPos(posToCell(pos));
		}

		private int[] findNeighbors(int cellno) {
			List<int> neighbors = new List<int> { -1, 1, -col, col, -col - 1, -col + 1, col - 1, col + 1 };

			if (cellno % col == 0) neighbors.RemoveAll((no) => { return no == -1 || no == -1 - col || no == -1 + col; });
			if (cellno % col == col - 1) neighbors.RemoveAll((no) => { return no == 1 || no == 1 - col || no == 1 + col; });
			if (cellno / col == 0) neighbors.RemoveAll((no) => { return no == -col || no == -col - 1 || no == -col + 1; });
			if (cellno / col == row - 1) neighbors.RemoveAll((no) => { return no == col || no == col - 1 || no == col + 1; });

			for (int i = 0; i < neighbors.Count;) {
				neighbors[i] += cellno;
				if (world[neighbors[i]].type == CellType.NotGround) {
					neighbors.RemoveAt(i);
				}
				else ++i;
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
			path.Add(from);
			path.Reverse();

			return path.ToArray();
		}

		private float computeDistance(int cell1, int cell2) {
			return Vector3.Distance(cellToPos(cell1), cellToPos(cell2));
		}
		
		private int[] findAstarPath(int from, int to) {
			int maxCells = row * col;

			if (from < 0 || from >= maxCells || to < 0 || to >= maxCells) return null;

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
						parents[neighbor] = current.no;
						return buildPath(parents, from, to);
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