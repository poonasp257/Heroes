using UnityEngine;
using UnityEngine.UI;

namespace Heroes {
	public class UISelectedCharacter : MonoBehaviour {
		private Text familyName;
		private Text characterName;

		private void Start() {
			familyName = transform.Find("Family Name").GetComponent<Text>();
			characterName = transform.Find("Character Name").GetComponent<Text>();
		}

		public void ChangeSelection(string name) {
			characterName.text = name;
		}
	}
}