using System.Diagnostics;
using UnityEngine;
using System.Threading.Tasks;

using Debug = UnityEngine.Debug;
using Newtonsoft.Json.Linq;
using Newtonsoft.Json;

namespace Heroes {
	public class MonsterDataBuilder : MonoBehaviour {
		private string convertToJson() {
			JArray rootArray = new JArray();
			foreach(var zone in transform) {
				var zoneTransform = zone as Transform;
				JObject zoneProperty = new JObject();
				JArray monsterArray = new JArray();
				foreach(var monster in zoneTransform) {
					var monsterTransform = monster as Transform;
					var monsterType = monsterTransform.GetComponent<MonsterType>();
					JObject monsterProperty = new JObject();
					monsterProperty.Add("typeId", monsterType.typeId);
					monsterProperty.Add("position", JsonUtility.ToJson(monsterTransform.position));
					monsterProperty.Add("rotation", JsonUtility.ToJson(monsterTransform.rotation.eulerAngles));
					monsterArray.Add(monsterProperty);
				}

				Vector3 center = zoneTransform.position;
				zoneProperty.Add("position", JsonUtility.ToJson(center));
				zoneProperty.Add("monsters", monsterArray);
				rootArray.Add(zoneProperty);
			}

			JObject rootProperty = new JObject();
			rootProperty.Add("monsterZones", rootArray);
			return JsonConvert.SerializeObject(rootProperty, Formatting.Indented);
		}

		public void buildData() {
			Util.MeasureExecutionTime("monster data build", async () => {
				await Util.AsyncCreateJsonFile("/Data", "monster_zone_info", this.convertToJson());
			});
		}
	}
}