using System;
using UnityEngine;
using UnityEngine.UI;

namespace Heroes {
	public class UISelectedCharacter : MonoBehaviour {
		private GameObject previewCharacter = null;
		[SerializeField] private Transform previewNode = null;
		[SerializeField] private Text familyNameText = null;
		[SerializeField] private Text characterNameText = null;

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
			characterNameText.text = characterInfo.name;
			CharacterId = characterInfo.id;
			if (previewCharacter) previewCharacter.SetActive(false);
			previewCharacter = previewNode.Find(characterInfo.type.ToString())?.gameObject;
			previewCharacter.SetActive(true);
		}

		public void deselectCharacter() {
			familyNameText.text = "";
			characterNameText.text = "";
		}
	}
}