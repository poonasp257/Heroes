using UnityEngine;
using UnityEditor;

namespace Heroes {
	[CustomEditor(typeof(WorldMapBuilder))]
	public class WorldMapBuildButton : Editor {
		public override void OnInspectorGUI() {
			base.OnInspectorGUI();

			var builder = this.target as WorldMapBuilder;
			if(GUILayout.Button("Build")) {
				builder.buildWorld();
			}
		}
	}
}