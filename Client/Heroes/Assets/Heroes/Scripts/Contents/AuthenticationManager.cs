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

		private void Start() {
			initialize();

			networkManager.RegisterNotification(PacketType.AuthLoginResponse, AuthLoginResponse);
			networkManager.RegisterNotification(PacketType.AuthRegisterResponse, AuthRegisterResponse);
		}
		
		private void Update() {
			updateInputField();
			processInput();
 		}

		private void initialize() {
			msgBox = GameObject.Find("MessageHandler").GetComponent<MessageBox>();
			networkManager = GameObject.Find("NetworkManager").GetComponent<NetworkManager>();

			GameObject inputField = GameObject.Find("UserIdField");
			if (!inputField) return;
			userIdField = inputField.GetComponent<InputField>();

			inputField = GameObject.Find("PasswordField");
			if (!inputField) return;
			passwordField = inputField.GetComponent<InputField>();

			userIdField.Select();
		}
		
		private void processInput() {
			if (msgBox.isExist()) return;

			if(Input.GetKeyDown(KeyCode.Return)
				|| Input.GetKeyDown(KeyCode.KeypadEnter)) {
				RequestLogin();
			}

			if (Input.GetKeyDown(KeyCode.Tab)) { 
				changeFocus();
			}
		}

		private void updateInputField() {
			userId = userIdField.text;
			password = passwordField.text;
		}	

		private void clearInputField() {
			userIdField.text = "";
			passwordField.text = "";
		}

		private void changeFocus() {
			if(userIdField.isFocused) {
				passwordField.Select();
//				passwordField.ActivateInputField();
			}
			else {
				userIdField.Select();
	//			userIdField.ActivateInputField();	
			}
		}

		private bool checkInputField() {
			if(string.IsNullOrEmpty(userId) 
				|| string.IsNullOrEmpty(password)) {
				return false;
			}

			return true;
		} 

		public void RequestLogin() {
			if (!checkInputField()) {
				msgBox.alert("잘못된 입력입니다.");
				return;
			}

			AuthLoginRequestPacket packet = new AuthLoginRequestPacket();
			packet.id = userId;
			packet.password = password;

			networkManager.send(packet);
			clearInputField();

			msgBox.notice("서버 요청을 기다리고 있습니다.");
		}

		public void RequestRegister() {		
			if (!checkInputField()) {
				msgBox.alert("잘못된 입력입니다.");
				return;
			}
				
			AuthRegisterRequestPacket packet = new AuthRegisterRequestPacket();
			packet.id = userId;
			packet.password = password;

			networkManager.send(packet);
			clearInputField();
		}

		public void AuthLoginResponse(PacketType type, Packet rowPacket) {
			AuthLoginResponsePacket packet = rowPacket as AuthLoginResponsePacket;
			if(packet == null) {
				Debug.Log("invalid packet");
				return;
			}

			if(!packet.success) {
				msgBox.alert("로그인 정보가 일치하지 않습니다.");
				return;
			}
			
			GameObject obj = new GameObject();
			obj.AddComponent<LobbyManager>();
			DontDestroyOnLoad(obj);

			SceneManager.LoadScene("Chanel");
		}

		public void AuthRegisterResponse(PacketType type, Packet rowPacket) {
			AuthRegisterResponsePacket packet = rowPacket as AuthRegisterResponsePacket;
			if(packet == null) {
				Debug.Log("invalid packet");
				return;
			}

			if(!packet.success) {
				Debug.Log("Register Failed");
				return;
			}

			msgBox.close();

			//SceneManager.LoadScene("Chanel");
		}
	}
}