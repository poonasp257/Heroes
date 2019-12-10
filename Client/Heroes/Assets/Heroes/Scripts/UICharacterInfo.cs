﻿using System;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

namespace Heroes {
	public class UICharacterInfo : MonoBehaviour, IScrollHandler {
		private UISelectedCharacter selectedCharacterUI;
		private ScrollRect scrollRect;

		private CharacterInfo characterInfo;

		private Image classIcon;
		private Text level;
		private Text characterName;
		private Text location;
		
		[SerializeField] private Sprite[] classIcons;

		public CharacterInfo Info {
			get { return characterInfo; }
			set {
				classIcon.sprite = classIcons[(int)value.characterClass];
				level.text = value.level.ToString();
				characterName.text = value.characterName;
				location.text = value.location;
				characterInfo = value;
			}
		}

		private void Awake() {
			classIcon = transform.Find("Class Icon").GetComponent<Image>();
			level = transform.Find("Level").GetComponent<Text>();
			characterName = transform.Find("Character Name").GetComponent<Text>();
			location = transform.Find("Location").GetComponent<Text>();
		}

		private void Start() {
			selectedCharacterUI = GameObject.Find("Selected Character").GetComponent<UISelectedCharacter>();
			scrollRect = GetComponentInParent<ScrollRect>();
		}

		public void OnClick() {
			selectedCharacterUI.SelectCharacter(this);
		}		
				
		public void OnConnectButtonClick() {
			PlayerData.Instance.CharacterId = Info.characterId;
			LoadingSceneManager.LoadScene("Town");
		}

		public void OnScroll(PointerEventData eventData) {
			scrollRect.OnScroll(eventData);
		}
	}
}