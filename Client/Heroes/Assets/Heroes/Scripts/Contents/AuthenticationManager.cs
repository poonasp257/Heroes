using System;
using System.Collections;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;
using UnityEngine.SceneManagement;

namespace Heroes {
	public class AuthenticationManager : MonoBehaviour {
		private MessageBox		msgBox;
		private NetworkManager	networkManager;
		private InputField		userIdField;
		private InputField		passwordField;
		private Button			loginButton;
		private Button			registerButton;

		private string userId;
		private string password;

		private void Start() {
			initialize();

			networkManager.RegisterNotification(PacketType.AuthLoginResponse, authLoginResponse);
			networkManager.RegisterNotification(PacketType.AuthRegisterResponse, authRegisterResponse);
		}
		
		private void Update() {
			if (msgBox.isExist()) return;

			activateInteractableUI();
			updateInputField();
			processInput();
 		}

		private void initialize() {
			msgBox = GameObject.Find("Message Handler").GetComponent<MessageBox>();
			networkManager = GameObject.Find("Network Manager").GetComponent<NetworkManager>();

			userIdField = GameObject.Find("UserIdField").GetComponent<InputField>();
			passwordField = GameObject.Find("PasswordField").GetComponent<InputField>();
			loginButton = GameObject.Find("Login").GetComponent<Button>();
			registerButton = GameObject.Find("Register").GetComponent<Button>();
			
			userIdField.Select();
		}
		
		private void processInput() {			
			if (Input.GetKeyDown(KeyCode.Return)
				|| Input.GetKeyDown(KeyCode.KeypadEnter)) {
				authLoginRequest();
			}

			if (Input.GetKeyDown(KeyCode.Tab)) { 
				changeFocus();
			}
		}

		private void deactivateInteractableUI() {
			userIdField.interactable = false;
			passwordField.interactable = false;
			loginButton.interactable = false;
			registerButton.interactable = false;
		}

		private void activateInteractableUI() {
			userIdField.interactable = true;
			passwordField.interactable = true;
			loginButton.interactable = true;
			registerButton.interactable = true;
		}

		private void updateInputField() {
			userId = userIdField.text;
			password = passwordField.text;
		}	

		private void clearInputField() {
			userId = "";
			userIdField.text = "";
			password = "";
			passwordField.text = "";
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
			msgBox.close();

			AuthLoginResponsePacket packet = rowPacket as AuthLoginResponsePacket;
			if(packet == null) {
				Debug.Log("invalid packet");
				return;
			}

			if(packet.errorCode < 0) {
				msgBox.alert("로그인 정보가 일치하지 않습니다.");
				return;
			}

			StartCoroutine(LoadChanelScene(packet.accountId));
		}

		public void authRegisterResponse(PacketType type, Packet rowPacket) {
			msgBox.close();

			AuthRegisterResponsePacket packet = rowPacket as AuthRegisterResponsePacket;
			if(packet == null) {
				Debug.Log("invalid packet");
				return;
			}

			if(packet.errorCode < 0) {
				msgBox.alert("잘못된 입력 정보입니다.");
				return;
			}
			
			StartCoroutine(LoadChanelScene(packet.accountId));
		}

		public IEnumerator LoadChanelScene(UInt64 accountId) {
			AsyncOperation op = SceneManager.LoadSceneAsync("Chanel");
			op.allowSceneActivation = false;

			while (!op.isDone){
				yield return null;

				if (op.progress >= 0.9f) {
					GameObject lobbyManager = new GameObject("Lobby Manager");
					var component = lobbyManager.AddComponent<LobbyManager>();
					component.AccountId = accountId;
					DontDestroyOnLoad(lobbyManager);

					op.allowSceneActivation = true;
					yield break;
				}
			}						
		}
	}
}