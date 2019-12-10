using System;
using UnityEngine;
using UnityEngine.UI;

namespace Heroes {
	public class UICharacterClass : MonoBehaviour {
		private GameObject selectedClass;

		[SerializeField] private CharacterClass characterClass;

		private void Start() {
			gameObject.name = Enum.GetName(typeof(CharacterClass), characterClass);

			selectedClass = GameObject.Find("Selected Class");

			Button button = GetComponent<Button>();
			button.onClick.AddListener(OnClick);
		}

		private void OnClick() {
			if (!selectedClass) return;

			Text className = selectedClass.GetComponent<Text>();
			className.text = gameObject.name;
		}
	}
}