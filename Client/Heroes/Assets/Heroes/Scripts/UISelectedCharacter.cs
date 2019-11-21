using UnityEngine;
using UnityEngine.UI;

namespace Heroes {
	public class UISelectedCharacter : MonoBehaviour {
		private Text familyName;
		private Text characterName;

		public string FamilyName {
			get {
				return familyName.text;
			}
			set {
				familyName.text = value;
			}
		}

		public string CharacterName {
			get {
				return characterName.text;
			}
			set {
				characterName.text = value;
			}
		}

		private void Awake() {
			familyName = transform.Find("Family Name").GetComponent<Text>();
			characterName = transform.Find("Character Name").GetComponent<Text>();
		}
	}
}