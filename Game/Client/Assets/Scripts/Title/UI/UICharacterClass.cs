using System;
using UnityEngine;
using UnityEngine.UI;

namespace Heroes {
	public class UICharacterClass : MonoBehaviour {
		private Button button;

		[SerializeField] private CreateCharacterManager createCharacterManager = null;
		[SerializeField] private CharacterClass characterClass = CharacterClass.None;

		private void Start() {
			gameObject.name = Enum.GetName(typeof(CharacterClass), characterClass);
			button = gameObject.GetComponent<Button>();
			button.onClick.AddListener(() => 
				createCharacterManager.selectClass(characterClass));
		}
	}
}