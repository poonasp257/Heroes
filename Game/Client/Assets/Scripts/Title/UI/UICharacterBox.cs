﻿using System;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.Events;
using UnityEngine.EventSystems;

namespace Heroes {
	public class UICharacterBox : MonoBehaviour, IScrollHandler, IPointerEnterHandler, IPointerExitHandler {
        private AccountManager accountManager;
		private UISelectedCharacter selectedCharacterUI;
		private ScrollRect scrollRect;

		private UnityAction onClickAction;
		private UnityAction onConnectAction;
		private UnityAction onMoveUpAction;
		private UnityAction onMoveDownAction;

		private bool changePositionMode = false;

		private SceneLoader sceneLoader = null;

		[Header("Class Icon Sprites")]
		[SerializeField] private Sprite[] classIcons = null;

		[Header("Character Status")]
		[SerializeField] private Image classIcon = null;
		[SerializeField] private Text level = null;
		[SerializeField] private Text characterName = null;
		[SerializeField] private Text location = null;

		[Header("Interaction Button")]
		[SerializeField] private GameObject connectButton = null;
		[SerializeField] private GameObject orderButtons = null;
		[SerializeField] private UIButton moveUpButton = null;
		[SerializeField] private UIButton moveDownButton = null;

		public bool ChangePositionMode {
			get { return changePositionMode; } 
			set {
				changePositionMode = value;
				orderButtons.SetActive(value);
			}
		}

		private void Start() {
			var selectedCharacterUIObj = GameObject.Find("Selected Character");
			selectedCharacterUI = selectedCharacterUIObj?.GetComponent<UISelectedCharacter>();
			if (selectedCharacterUI == null) throw new Exception("UISelectedCharacter not found");
			
			var accountManagerObj = GameObject.Find("Account Manager");
			accountManager = accountManagerObj?.GetComponent<AccountManager>();
			if (accountManager == null) throw new Exception("Account Manager not found");
			
			var sceneLoaderObj = GameObject.Find("Scene Loader");
			sceneLoader = sceneLoaderObj?.GetComponent<SceneLoader>();
			if (sceneLoader == null) throw new Exception("Scene Loader not found");

			scrollRect = GetComponentInParent<ScrollRect>();			

			moveUpButton.onClick.AddListener(onMoveUpAction);
			moveDownButton.onClick.AddListener(onMoveDownAction);
		}

		private void OnMoveUp(int firstIndex, int lastIndex) {
			int fromIndex = this.transform.GetSiblingIndex();
			int toIndex = -1;

			if (fromIndex == firstIndex) toIndex = lastIndex;
			else toIndex = fromIndex - 1;

			accountManager.changeCharacterOrderRequest(fromIndex, toIndex);
		}

		private void OnMoveDown(int firstIndex, int lastIndex) {
			int fromIndex = this.transform.GetSiblingIndex();
			int toIndex = -1;

			if (fromIndex == lastIndex) toIndex = firstIndex;
			else toIndex = fromIndex + 1;

			accountManager.changeCharacterOrderRequest(fromIndex, toIndex);
		}
				
		public void initialize(CharacterInfo characterInfo, int createdCharactersCount) {
			classIcon.sprite = classIcons[(int)characterInfo.type - 1];
			level.text = "Lv. " + characterInfo.level.ToString();
			characterName.text = characterInfo.name;
			location.text = characterInfo.location;

			onClickAction = () => selectedCharacterUI.selectCharacter(
				AccountData.Instance.FamilyName, characterInfo);
			onConnectAction = () => {
				AccountData.Instance.CurrentCharacter = characterInfo;
				sceneLoader.LoadMainScene();
			};

			onMoveUpAction = () => this.OnMoveUp(0, createdCharactersCount - 1);
			onMoveDownAction = () => this.OnMoveDown(0, createdCharactersCount - 1);
		}

		public void OnClick() {
			onClickAction?.Invoke();
		}		
				
		public void OnConnect() {
			onConnectAction?.Invoke();
		}

		public void OnScroll(PointerEventData eventData) {
			scrollRect.OnScroll(eventData);
		}

		public void OnPointerEnter(PointerEventData eventData) {
			if (this.ChangePositionMode) return;

			connectButton.SetActive(true);
		}

		public void OnPointerExit(PointerEventData eventData) {
			if (this.ChangePositionMode) return;

			connectButton.SetActive(false);
		}
	}
}