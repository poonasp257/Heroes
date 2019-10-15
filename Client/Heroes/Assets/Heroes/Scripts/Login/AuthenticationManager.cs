using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

namespace Heroes {
	public class AuthenticationManager : MonoBehaviour {
		private NetworkManager	networkManager;
		private InputField		userIdField;
		private InputField		passwordField;

		private string userId;
		private string password;
		
		private void Start() {
			Initialize();
		}
		
		private void Update() {
			UpdateInputField();
			ProcessInput();
 		}

		private void Initialize() {
//			networkManager = new NetworkManager(9000, "127.0.0.1");
//			networkManager.CreateTCPSocket();
//			networkManager.Connect();

			GameObject inputField = GameObject.Find("UserIdField");
			if (!inputField) return;
			userIdField = inputField.GetComponent<InputField>();

			inputField = GameObject.Find("PasswordField");
			if (!inputField) return;
			passwordField = inputField.GetComponent<InputField>();
		}
		
		private void ProcessInput() {
			if(Input.GetKeyDown(KeyCode.KeypadEnter)) {
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

			Debug.Log(userId);
			Debug.Log(password);
		}

		public void RequestRegister() {
			Debug.Log(userId);
			Debug.Log(password);
		}
	}
}