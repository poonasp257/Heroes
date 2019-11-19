using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

namespace Heroes {
	public class MessageBox : MonoBehaviour {
		[SerializeField] private GameObject alertMsgBox;
		[SerializeField] private GameObject confirmMsgBox;
		[SerializeField] private GameObject noticeMsgBox;

		private bool isOpened;
		private GameObject msgBox;
		private Dictionary<MessageType, GameObject> msgBoxes;

		private void Start() {
			isOpened = false;

			msgBoxes = new Dictionary<MessageType, GameObject>();
			msgBoxes.Add(MessageType.Alert, alertMsgBox);
			msgBoxes.Add(MessageType.Confirm, confirmMsgBox);
			msgBoxes.Add(MessageType.Notice, noticeMsgBox);
		}

		public void Show(string msg, MessageType type) {
			if (isOpened) return;

			StartCoroutine(ShowMessageBox(msg, type));
		}

		public void Close() {
			if (!isOpened) return;

			Destroy(msgBox);
			msgBox = null;
		}

		public IEnumerator ShowMessageBox(string msg, MessageType type) {
			yield return null;
			GameObject canvas = GameObject.Find("Canvas");
			msgBox = Instantiate(msgBoxes[type], canvas.transform);

			Text message = msgBox.transform.Find("Message").GetComponent<Text>();
			message.text = msg;

			isOpened = true;
			while(msgBox != null) {
				
				
			}

			isOpened = false;
		}
	}
}
