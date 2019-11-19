using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

namespace Heroes {
	public class UICharacterInfo : MonoBehaviour {
		private UISelectedCharacter selectedCharacterUI;

		private Image classIcon;
		private Text level;
		private Text characterName;
		private Text location;
		
		private void Start() {
			selectedCharacterUI = GameObject.Find("Selected Character").GetComponent<UISelectedCharacter>();

			classIcon = transform.Find("Class Icon").GetComponent<Image>();
			level = transform.Find("Level").GetComponent<Text>();
			characterName = transform.Find("Character Name").GetComponent<Text>();
			location = transform.Find("Location").GetComponent<Text>();

		}

		public void OnClick() {
			selectedCharacterUI.ChangeSelection(characterName.text);
		}
	}
}