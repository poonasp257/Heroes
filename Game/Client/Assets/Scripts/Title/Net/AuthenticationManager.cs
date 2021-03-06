﻿using System;
using System.Collections;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using UnityEngine.Networking;
using Newtonsoft.Json.Linq;

namespace Heroes {
	public class AuthenticationManager : MonoBehaviour {
		private MessageBoxHandler messageBoxHandler;

		[Header("Input Fields")]
		[SerializeField] private InputField userIdField = null;
		[SerializeField] private InputField passwordField = null;

		[Header("Authentication Server Information")]
		[SerializeField] private string homepageIP = "http://127.0.0.1:8000";
		[SerializeField] private string authServerIP = "http://127.0.0.1:9000";

		private void Start() {
			var msgHandlerObject = GameObject.Find("MessageBox Handler");
			messageBoxHandler = msgHandlerObject?.GetComponent<MessageBoxHandler>();
			if (messageBoxHandler == null) throw new Exception("MessageBox Handler not found");
 
			userIdField.ActivateInputField();
		}
		
		private void Update() {
			if (!messageBoxHandler.IsOpened) { 
				processInput();
			}
 		}

		private void processInput() {
			if (Input.GetButtonDown("Submit")) {
				requestLogin();
			}
			if (Input.GetKeyDown(KeyCode.Tab)) { 
				changeFocus();
			}
		}

		private void changeFocus() {
			if (userIdField.isFocused) passwordField.Select();
			else userIdField.Select();
		} 
		
		private IEnumerator RequestLogin() {
			messageBoxHandler.notice("처리 중입니다.");

			WWWForm form = new WWWForm();
			form.AddField("username", userIdField.text);
			form.AddField("password", passwordField.text);

			UnityWebRequest webRequest = UnityWebRequest.Post(authServerIP + "/account/signin", form);
			yield return webRequest.SendWebRequest();
			if (webRequest.isNetworkError || webRequest.isHttpError) {
				messageBoxHandler.alert("네트워크 상태가 원활하지 않습니다.");
				yield break;
			}

			messageBoxHandler.close();
			string response = webRequest.downloadHandler.text;
			JObject responseData = JObject.Parse(response);
			if(responseData.ContainsKey("error")) {
				messageBoxHandler.alert(responseData["error"].ToString());
				yield break;
			}

			AccountData.Instance.accessKey = responseData["accessKey"].ToString();
			SceneManager.LoadScene("Channel");
		}

		public void requestLogin() {
			if (string.IsNullOrWhiteSpace(userIdField.text)) {
				messageBoxHandler.alert("아이디를 입력해주세요.");
				return;
			}
			if (string.IsNullOrWhiteSpace(passwordField.text)) {
				messageBoxHandler.alert("비밀번호를 입력해주세요.");
				return;
			}

			StartCoroutine("RequestLogin");
		}

		public void openHelpAccountPage() {
			Application.OpenURL(homepageIP + "/help/account");
		}
		public void openHelpPasswordPage() {
			Application.OpenURL(homepageIP + "/help/password");
		}

		public void openRegisterPage() {
			Application.OpenURL(homepageIP + "/signup");
		}
	}
}