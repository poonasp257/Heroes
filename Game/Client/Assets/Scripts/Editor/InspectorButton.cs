using UnityEngine;
using UnityEditor;

namespace Heroes {
	[CustomEditor(typeof(WorldMapBuilder))]
	public class WorldMapBuildButton : Editor {
		public override void OnInspectorGUI() {
			base.OnInspectorGUI();

			var builder = this.target as WorldMapBuilder;
			if(GUILayout.Button("Build World Map")) {
				builder.buildWorldMap();
			}
		}
	}

	[CustomEditor(typeof(MonsterDataBuilder))]
	public class MonsterDataBuildButton : Editor {
		public override void OnInspectorGUI() {
			base.OnInspectorGUI();

			var builder = this.target as MonsterDataBuilder;
			if (GUILayout.Button("Build")) {
				builder.buildData();
			}
		}
	}
}