﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

namespace Heroes {
	public class AuthenticationManager : MonoBehaviour {
		private MessageBox		msgBox;
		private NetworkManager	networkManager;
		private InputField		userIdField;
		private InputField		passwordField;

		private string userId;
		private string password;

		private List<Button> buttonList;
		[SerializeField] private GameObject	loginPage;
		[SerializeField] private GameObject	registerPage;
		
		private void Start() {
			initialize();

			networkManager.RegisterNotification(PacketType.AuthLoginResponse, authLoginResponse);
			networkManager.RegisterNotification(PacketType.AuthRegisterResponse, authRegisterResponse);
		}
		
		private void Update() {
			if (msgBox.IsExist) return;

			activateInteractableUI();
			updateInputField();
			processInput();
 		}

		private void initialize() {
			msgBox = GameObject.Find("Message Handler").GetComponent<MessageBox>();
			networkManager = GameObject.Find("Network Manager").GetComponent<NetworkManager>();

			userIdField = GameObject.Find("UserIdField").GetComponent<InputField>();
			passwordField = GameObject.Find("PasswordField").GetComponent<InputField>();

			if (loginPage == null || registerPage == null) {
				Debug.Log("login or register object isn't assgined.");
				return;
			}

			buttonList = new List<Button>();

			Button[] buttons = loginPage.GetComponentsInChildren<Button>();
			foreach(var button in buttons) {
				buttonList.Add(button);
			}

			buttons = registerPage.GetComponentsInChildren<Button>();
			foreach(var button in buttons) {
				buttonList.Add(button);
			}
			
			userIdField.Select();
		}
		
		private void processInput() {			
			if (Input.GetKeyDown(KeyCode.Return) || Input.GetKeyDown(KeyCode.KeypadEnter)) {
				if (loginPage.activeSelf) authLoginRequest();
				else authRegisterRequest();
			}

			if (Input.GetKeyDown(KeyCode.Tab)) { 
				changeFocus();
			}
		}

		private void deactivateInteractableUI() {
			userIdField.interactable = false;
			passwordField.interactable = false;

			foreach(var button in buttonList) {
				button.interactable = false;
			}
		}

		private void activateInteractableUI() {
			userIdField.interactable = true;
			passwordField.interactable = true;

			foreach(var button in buttonList) {
				button.interactable = true;
			}
		}

		private void updateInputField() {
			userId = userIdField.text;
			password = passwordField.text;
		}	

		private void changeFocus() {
			if(userIdField.isFocused) passwordField.Select();
			else userIdField.Select();
		}

		private bool checkInputField() {
			if(string.IsNullOrEmpty(userId) 
				|| string.IsNullOrEmpty(password)) {
				return false;
			}

			return true;
		} 

		public void clearInputField() {
			userId = "";
			userIdField.text = "";
			password = "";
			passwordField.text = "";
		}

		public void authLoginRequest() {
			if (!checkInputField()) {
				msgBox.alert("잘못된 입력입니다.");
				return;
			}

			AuthLoginRequestPacket packet = new AuthLoginRequestPacket();
			packet.id = userId;
			packet.password = password;

			networkManager.send(packet);
			clearInputField();
			deactivateInteractableUI();

			msgBox.notice("서버 요청을 기다리고 있습니다.");
		}

		public void authRegisterRequest() {		
			if (!checkInputField()) {
				msgBox.alert("잘못된 입력입니다.");
				return;
			}
				
			AuthRegisterRequestPacket packet = new AuthRegisterRequestPacket();
			packet.id = userId;
			packet.password = password;

			networkManager.send(packet);
			clearInputField();
			deactivateInteractableUI();

			msgBox.notice("서버 요청을 기다리고 있습니다.");
		}

		public void authLoginResponse(PacketType type, Packet rowPacket) {
			AuthLoginResponsePacket packet = rowPacket as AuthLoginResponsePacket;
			if(packet == null) {
				Debug.Log("invalid packet");
				return;
			}

			if(packet.errorCode >= 0) {
				msgBox.alert("로그인 정보가 일치하지 않습니다.");
				return;
			}

			PlayerData.Instance.AccountId = packet.accountId;
			StartCoroutine(LoadChanelScene());
		}

		public void authRegisterResponse(PacketType type, Packet rowPacket) {
			AuthRegisterResponsePacket packet = rowPacket as AuthRegisterResponsePacket;
			if(packet == null) {
				Debug.Log("invalid packet");
				return;
			}

			if(packet.errorCode >= 0) {
				msgBox.alert("잘못된 입력 정보입니다.");
				return;
			}

			loginPage.SetActive(true);
			registerPage.SetActive(false);

			msgBox.alert("회원가입 성공!");
		}

		public IEnumerator LoadChanelScene() {
			AsyncOperation op = SceneManager.LoadSceneAsync("Chanel");
			op.allowSceneActivation = false;

			while (!op.isDone){
				yield return null;

				if (op.progress >= 0.9f) {
					op.allowSceneActivation = true;
					msgBox.close();
					yield break;
				}
			}						
		}
	}
}