using System;
using UnityEngine;
using UnityEngine.UI;

namespace Heroes {
	public class UISelectedCharacter : MonoBehaviour {
		private Text familyName;
		private Text characterName;

		public CharacterInfo Info { get; set; }

		private void Awake() {
			familyName = transform.Find("Family Name").GetComponent<Text>();
			characterName = transform.Find("Character Name").GetComponent<Text>();

			familyName.text = "";
			characterName.text = "";
		}

		public void SelectCharacter(UICharacterInfo character) {
			UICharacterInfo selectedCharacter = character.GetComponent<UICharacterInfo>();
			Info = selectedCharacter.Info;

			familyName.text = Info.familyName;
			characterName.text = Info.characterName;
		}

		public bool isSelected() {
			return string.IsNullOrEmpty(Info.characterName) == false;
		}
	}
}