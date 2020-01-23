using System;
using System.Collections;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using UnityEngine.Networking;
using Newtonsoft.Json.Linq;

namespace Heroes {
	public class AuthenticationManager : MonoBehaviour {
		private MessageBox msgBox;

		private InputField userIdField;
		private InputField passwordField;

		[SerializeField] private Button loginButton;
		[SerializeField] private Button registerButton;

		private const string authenticationServerUrl = "http://localhost:3000";

		private void Start() {
			findGameObjects();
			userIdField.ActivateInputField();
		}
		
		private void Update() {
			processInput();
 		}

		private void findGameObjects() {
			msgBox = GameObject.Find("Message Handler").GetComponent<MessageBox>();
			userIdField = GameObject.Find("UserId Field").GetComponent<InputField>();
			passwordField = GameObject.Find("Password Field").GetComponent<InputField>();
		}
				
		private void processInput() {			
			if (Input.GetKeyDown(KeyCode.Return) 
				|| Input.GetKeyDown(KeyCode.KeypadEnter)) {
				requestLogin();
			}

			if (Input.GetKeyDown(KeyCode.Tab)) { 
				changeFocus();
			}
		}

		private void activateInteractableUI() {
			userIdField.interactable = true;
			passwordField.interactable = true;

			loginButton.interactable = true;
			registerButton.interactable = true;
		}

		private void deactivateInteractableUI() {
			userIdField.interactable = false;
			passwordField.interactable = false;

			loginButton.interactable = false;
			registerButton.interactable = false;
		}

		private void changeFocus() {
			if(userIdField.isFocused) passwordField.Select();
			else userIdField.Select();
		}

		private bool isFilledAllInputFields() {
			if(string.IsNullOrEmpty(userIdField.text) 
				|| string.IsNullOrEmpty(passwordField.text)) {
				return false;
			}

			return true;
		} 

		public void clearInputField() {
			userIdField.text = "";
			passwordField.text = "";
		}

		public void openHelpPage() {
			Application.OpenURL(authenticationServerUrl + "/help");
		}

		public void openRegisterPage() {
			Application.OpenURL(authenticationServerUrl + "/signup");
		}

		public void requestLogin() {
			if(string.IsNullOrWhiteSpace(userIdField.text)) {
				msgBox.alert("아이디를 입력해주세요.");
				return;
			}
			if(string.IsNullOrWhiteSpace(passwordField.text)) {
				msgBox.alert("비밀번호를 입력해주세요.");
				return;
			}

			StartCoroutine("RequestLogin");
		}

		private IEnumerator RequestLogin() {
			if (!isFilledAllInputFields()) yield break;

			msgBox.notice("서버의 응답을 기다리고 있습니다.");

			WWWForm form = new WWWForm();
			form.AddField("username", userIdField.text);
			form.AddField("password", passwordField.text);

			clearInputField();
			deactivateInteractableUI();

			UnityWebRequest webRequest = UnityWebRequest.Post(
				authenticationServerUrl + "/account/signin", form);
			yield return webRequest.SendWebRequest();

			msgBox.close();
			activateInteractableUI();

			if (webRequest.isNetworkError) {
				msgBox.alert("네트워크 상태가 원활하지 않습니다.");
				yield break;
			}

			string response = webRequest.downloadHandler.text;
			JObject responseData = JObject.Parse(response);

			if (webRequest.isHttpError) {
				msgBox.alert(responseData["message"].ToString());
				yield break;
			}

			UInt64 accountId = (UInt64)responseData["accountId"];
			PlayerData.Instance.AccountId = accountId;
			
			StartCoroutine("LoadChannelScene");
		}

		private IEnumerator LoadChannelScene() {
			AsyncOperation op = SceneManager.LoadSceneAsync("Channel");
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