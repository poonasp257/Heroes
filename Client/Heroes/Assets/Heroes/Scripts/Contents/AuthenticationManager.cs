using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

namespace Heroes {
	public class AuthenticationManager : MonoBehaviour {
		private NetworkManager	networkManager;
		private InputField		userIdField;
		private InputField		passwordField;

		private string userId;
		private string password;

		private void Start() {
			Initialize();

			networkManager.RegisterNotification(PacketType.AuthLoginResponse, ResponseLogin);
			networkManager.RegisterNotification(PacketType.AuthRegisterResponse, ResponseRegister);
		}
		
		private void Update() {
			UpdateInputField();
			ProcessInput();
 		}

		private void Initialize() {
			networkManager = GameObject.Find("NetworkManager").GetComponent<NetworkManager>();

			GameObject inputField = GameObject.Find("UserIdField");
			if (!inputField) return;
			userIdField = inputField.GetComponent<InputField>();

			inputField = GameObject.Find("PasswordField");
			if (!inputField) return;
			passwordField = inputField.GetComponent<InputField>();
		}
		
		private void ProcessInput() {
			if(Input.GetKeyDown(KeyCode.Return)
				|| Input.GetKeyDown(KeyCode.KeypadEnter)) {
				RequestLogin();
			}

			if (Input.GetKeyDown(KeyCode.Tab)) { 
				ChangeFocus();
			}
		}

		private void UpdateInputField() {
			userId = userIdField.text;
			password = passwordField.text;
		}	

		private void ChangeFocus() {
			if(userIdField.isFocused) {
				passwordField.Select();
				passwordField.ActivateInputField();
			}
			else {
				userIdField.Select();
				userIdField.ActivateInputField();	
			}
		}

		public void RequestLogin() {
			if(string.IsNullOrEmpty(userId)
				|| string.IsNullOrEmpty(password)) {
					Debug.Log("fill the input field");
					return;
				}

			AuthLoginRequestPacket packet = new AuthLoginRequestPacket();
			packet.id = userId;
			packet.password = password;
			networkManager.send(packet);
		}

		public void RequestRegister() {		
			if(string.IsNullOrEmpty(userId)
				|| string.IsNullOrEmpty(password)) {
					Debug.Log("fill the input field");
					return;
				}
				
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

			SceneManager.LoadScene("Select");
		}

		public void ResponseRegister(PacketType type, Packet rowPacket) {
			AuthRegisterResponsePacket packet = rowPacket as AuthRegisterResponsePacket;
			if(packet == null) {
				Debug.Log("invalid packet");
				return;
			}

			if(!packet.success) {
				Debug.Log("Login Failed");
				return;
			}

			LoadingSceneManager.LoadScene("Town");
		}
	}
}