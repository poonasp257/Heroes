using System.Collections;
using System.Diagnostics;
using UnityEngine;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.Threading.Tasks;

using Debug = UnityEngine.Debug;

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

		private void drawGrid(Cell[] world) {
			if (world == null) return;

			foreach(var cell in world) {
				Gizmos.color = cell.type == CellType.Ground ? Color.blue : Color.red;
				Gizmos.DrawWireCube(cell.position, Vector3.one * cellSize);
			}
		}

		private WorldMapData generateWorldMap() {
			int row = Mathf.CeilToInt(width / cellSize);
			int col = Mathf.CeilToInt(height / cellSize);
			int numOfCells = row * col;
			Cell[] world = new Cell[numOfCells];

			Vector3 center = this.transform.position + Vector3.one * cellSize * 0.5f;
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

		private string serializeWorldMap(WorldMapData worldMap) {
			var jArray = new JArray();
			foreach (var cell in worldMap.map) {
				jArray.Add(JsonUtility.ToJson(cell));
			}
			var jsonData = new JObject {
				["center"] = JsonUtility.ToJson(worldMap.center),
				["width"] = worldMap.width,
				["height"] = worldMap.height,
				["row"] = worldMap.row,
				["column"] = worldMap.column,
				["cellSize"] = worldMap.cellSize,
				["worldMap"] = jArray
			};

			return JsonConvert.SerializeObject(jsonData, Formatting.Indented);
		}

		public async Task buildWorld() {
			Stopwatch timer = Stopwatch.StartNew();
			Debug.Log("build started...");

			WorldMapData worldMap = generateWorldMap();
			string path = Application.dataPath + "/Data";
			await Util.CreateJsonFile(path, "WorldMap", serializeWorldMap(worldMap));

			timer.Stop();
			float endTime = timer.ElapsedMilliseconds * 0.001f;
			Debug.Log(string.Format("build finished: {0:0.000}s", endTime)); 
		}
	}
}