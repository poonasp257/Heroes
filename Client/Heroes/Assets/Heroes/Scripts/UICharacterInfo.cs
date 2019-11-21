using System;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

namespace Heroes {
	public class UICharacterInfo : MonoBehaviour, IScrollHandler {
		private UISelectedCharacter selectedCharacterUI;
		private ScrollRect scrollRect;

		private Image classIcon;
		private Text level;
		private Text characterName;
		private Text location;

		public UInt64 ID {
			get; set;
		}

		public UInt16 Class {
			get; set;
		}
	
		public UInt32 Level {				
			get {
				return UInt32.Parse(level.text);
			}
			set {
				level.text = value.ToString();
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

		public string Location {
			get {
				return location.text;
			}
			set {
				location.text = value;
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
			selectedCharacterUI.CharacterName = characterName.text;
		}		
				
		public void OnConnectButtonClick() {
			LobbyManager lobbyManager = GameObject.Find("Lobby Manager").GetComponent<LobbyManager>();
			lobbyManager.connectChanelRequest();
		}

		public void OnScroll(PointerEventData eventData) {
			scrollRect.OnScroll(eventData);
		}
	}
}