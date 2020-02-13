using System;
using UnityEngine;
using UnityEngine.UI;

namespace Heroes {
	public class UISelectedCharacter : MonoBehaviour {
		[SerializeField] private Text familyNameText;
		[SerializeField] private Text characterNameText;

		public bool IsSelected { 
			get { 
				return !string.IsNullOrWhiteSpace(familyNameText.text);
			} 
		}

		public UInt64 CharacterId { get; set; }

		private void Start() {
			familyNameText.text = "";
			characterNameText.text = "";
		}

		public void selectCharacter(string familyName, CharacterInfo characterInfo) {
			familyNameText.text = familyName;
			characterNameText.text = characterInfo.characterName;
			CharacterId = characterInfo.characterId;
		}

		public void deselectCharacter() {
			familyNameText.text = "";
			characterNameText.text = "";
		}
	}
}