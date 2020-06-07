using System;
using UnityEngine;
using UnityEngine.UI;

namespace Heroes {
	public class UICharacterClass : MonoBehaviour {
		private Button button;
		private Text className;
		[SerializeField] private CreateCharacterManager createCharacterManager = null;
		[SerializeField] private CharacterClassType type = CharacterClassType.None;

		private void Start() {
			var nameObj = transform.Find("Name/Text");
			className = nameObj?.GetComponent<Text>();
			gameObject.name = Enum.GetName(typeof(CharacterClassType), type);
			className.text = createCharacterManager.getName(type);

			button = gameObject.GetComponent<Button>();
			button.onClick.AddListener(() => 
				createCharacterManager.selectClass(type));
		}
	}
}