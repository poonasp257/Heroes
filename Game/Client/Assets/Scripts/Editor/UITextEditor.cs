using UnityEditor;
using UnityEditor.UI;

namespace Heroes {
	[CustomEditor(typeof(UIText))]
	public class UITextEditor : TextEditor {
		private SerializedProperty enableWordWrap;

		protected override void OnEnable() {
			base.OnEnable();
			enableWordWrap = serializedObject.FindProperty("enableWordWrap");
		}

		public override void OnInspectorGUI() {
			base.OnInspectorGUI();
			serializedObject.Update();
			EditorGUILayout.PropertyField(enableWordWrap);
			serializedObject.ApplyModifiedProperties();
		}
	}
}