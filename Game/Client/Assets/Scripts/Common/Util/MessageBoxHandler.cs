﻿using UnityEngine;
using UnityEngine.UI;
using UnityEngine.Events;

namespace Heroes {
	public class MessageBoxHandler : MonoBehaviour {
		[SerializeField] private GameObject alertMsgBox = null;
		[SerializeField] private GameObject confirmMsgBox = null;
		[SerializeField] private GameObject noticeMsgBox = null;

		private GameObject messageBox;

		public bool IsOpened { get { return messageBox != null; } }

		private void Start() {
			DontDestroyOnLoad(this.gameObject);
		}

		private void OnDestroy() {
			if (IsOpened) this.close();
		}

		private GameObject createMessageBox(GameObject prefab, string msg) {
			GameObject canvas = GameObject.Find("Canvas");
			var newMessageBox = Instantiate(prefab, canvas.transform);

			Text message = newMessageBox.transform.Find("Content/Message").GetComponent<Text>();
			message.text = msg;

			return newMessageBox;
		}

		public void alert(string msg, UnityAction okEvent = null) {
			if (IsOpened) this.close();

			messageBox = createMessageBox(alertMsgBox, msg);

			GameObject button = messageBox.transform.Find("Content/OK").gameObject;
			UIButton okButton = button.GetComponent<UIButton>();

			okButton.registerAction(this.close);
			if(okEvent != null) okButton.registerAction(okEvent);
			okButton.Select();
		}

		public void confirm(string msg, UnityAction yesEvent, UnityAction noEvent = null) {
			if (IsOpened) this.close();

			messageBox = createMessageBox(confirmMsgBox, msg);
			
			GameObject button = messageBox.transform.Find("Content/Buttons/Yes").gameObject;
			UIButton yesButton = button.GetComponent<UIButton>();

			yesButton.registerAction(this.close);
			if(yesEvent != null) yesButton.registerAction(yesEvent);
			yesButton.Select();

			button = messageBox.transform.Find("Content/Buttons/No").gameObject;
			UIButton noButton = button.GetComponent<UIButton>();

			noButton.registerAction(this.close);
			if (noEvent != null) noButton.registerAction(noEvent);
		}

		public void notice(string msg) {
			if (IsOpened) this.close();

			messageBox = createMessageBox(noticeMsgBox, msg);
		}

		public void close() {
			Destroy(messageBox);
		}
	}
}