using System.Threading.Tasks;
using UnityEngine;

namespace Heroes {
	public class WorldMapBuilder : MonoBehaviour {
		[Header("Setting")]
		[SerializeField] private int width = 0;
		[SerializeField] private int height = 0;
		[SerializeField] private float cellSize = 0;

		private void OnDrawGizmos() {
			Vector3 originPoint = this.transform.position;
			Vector3 cubeSize = new Vector3(width, 0, height);

			Gizmos.color = Color.yellow;
			Gizmos.DrawWireCube(originPoint, cubeSize);
		}

		private WorldMapData generateWorldMap() {
			int row = Mathf.CeilToInt(width / cellSize);
			int col = Mathf.CeilToInt(height / cellSize);
			int numOfCells = row * col;
			Cell[] world = new Cell[numOfCells];

			Vector3 center = this.transform.position;
			Vector3 bottomLeft = center - new Vector3(width * 0.5f, 0, height * 0.5f);
			int layerMask = (1 << LayerMask.NameToLayer("Enviroment"))
				| (1 << LayerMask.NameToLayer("Water"));
			for (int i = 0; i < numOfCells; ++i) {
				Vector3 cellPos = bottomLeft + new Vector3(i % col, 0, i / col) * cellSize;
				bool isGround = !Physics.CheckSphere(cellPos, cellSize, layerMask);
				CellType type = isGround ? CellType.Ground : CellType.NotGround;
				world[i] = new Cell(cellPos, type);
			}

			return new WorldMapData {
				center = center,
				row = row,
				column = col,
				width = width,
				height = height,
				cellSize = cellSize,
				map = world
			};
		}
				
		public void buildWorldMap() {
			WorldMapData worldMapData = new WorldMapData();
			Util.MeasureExecutionTime("world build", async () => {
				worldMapData = this.generateWorldMap();
				await Util.AsyncCreateJsonFile("/Data", "world_map", JsonUtility.ToJson(worldMapData, true));
			});
        }
	}
}