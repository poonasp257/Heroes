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

			networkManager.RegisterNotification(PacketType.AuthLoginResponse, ResponseLogin);
			networkManager.RegisterNotification(PacketType.AuthRegisterResponse, ResponseRegister);
		}
		
		private void Update() {
			updateInputField();
			processInput();
 		}

		private void initialize() {
			msgBox = GetComponent<MessageBox>();
			networkManager = GameObject.Find("NetworkManager").GetComponent<NetworkManager>();

			GameObject inputField = GameObject.Find("UserIdField");
			if (!inputField) return;
			userIdField = inputField.GetComponent<InputField>();

			inputField = GameObject.Find("PasswordField");
			if (!inputField) return;
			passwordField = inputField.GetComponent<InputField>();
		}
		
		private void processInput() {
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

		private void changeFocus() {
			if(userIdField.isFocused) {
				passwordField.Select();
				passwordField.ActivateInputField();
			}
			else {
				userIdField.Select();
				userIdField.ActivateInputField();	
			}
		}

		private bool checkInputField() {
			if(string.IsNullOrEmpty(userId) 
				|| string.IsNullOrEmpty(password)) {
					msgBox.Show("잘못된 입력입니다.", MessageType.Alert);
					return false;
				}

			return true;
		} 

		public void RequestLogin() {
			if (!checkInputField()) return;

			AuthLoginRequestPacket packet = new AuthLoginRequestPacket();
			packet.id = userId;
			packet.password = password;
			networkManager.send(packet);
		}

		public void RequestRegister() {		
			if (!checkInputField()) return;
				
			AuthRegisterRequestPacket packet = new AuthRegisterRequestPacket();
			packet.id = userId;
			packet.password = password;
			networkManager.send(packet);
		}

		public void ResponseLogin(PacketType type, Packet rowPacket) {
			AuthLoginResponsePacket packet = rowPacket as AuthLoginResponsePacket;
			if(packet == null) {
				Debug.Log("invalid packet");
				return;
			}

			if(!packet.success) {
				Debug.Log("Login Failed");
				return;
			}

			GameObject obj = new GameObject();
			obj.AddComponent<LobbyManager>();
			DontDestroyOnLoad(obj);

			SceneManager.LoadScene("Chanel");
		}

		public void ResponseRegister(PacketType type, Packet rowPacket) {
			AuthRegisterResponsePacket packet = rowPacket as AuthRegisterResponsePacket;
			if(packet == null) {
				Debug.Log("invalid packet");
				return;
			}

			if(!packet.success) {
				Debug.Log("Register Failed");
				return;
			}

			//SceneManager.LoadScene("Chanel");
		}
	}
}