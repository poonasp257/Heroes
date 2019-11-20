using UnityEngine.Events;
using UnityEngine;
using UnityEngine.UI;

namespace Heroes {
	public class MessageBox : MonoBehaviour {
		[SerializeField] private GameObject alertMsgBox;
		[SerializeField] private GameObject confirmMsgBox;
		[SerializeField] private GameObject noticeMsgBox;
		
		private GameObject msgBox;

		private void Start() {
			DontDestroyOnLoad(this.gameObject);
		}

		private void OnDestroy() {
			if(msgBox) Destroy(msgBox);
		}

		private void setupMsgBox(GameObject prefab, string msg) {
			GameObject canvas = GameObject.Find("Canvas");
			msgBox = Instantiate(prefab, canvas.transform);

			Text message = msgBox.transform.Find("Content/Message").GetComponent<Text>();
			message.text = msg;
		}

		private void destroyMsgBox() {
			Destroy(msgBox);
			msgBox = null;
		}

		public bool isExist() {
			return msgBox != null; 
		}

		public void alert(string msg) {
			if (msgBox) this.close();

			setupMsgBox(alertMsgBox, msg);

			GameObject button = msgBox.transform.Find("Content/OK").gameObject;
			Button okButton = button.GetComponent<Button>();
			okButton.onClick.AddListener(destroyMsgBox);
		}

		public bool confirm(string msg, UnityAction yesEvent, UnityAction noEvent) {
			if (msgBox) this.close();

			setupMsgBox(confirmMsgBox, msg);
			
			GameObject button = msgBox.transform.Find("Content/Buttons/Yes").gameObject;
			Button yesButton = button.GetComponent<Button>();
			yesButton.onClick.AddListener(yesEvent);
			yesButton.onClick.AddListener(destroyMsgBox);

			button = msgBox.transform.Find("Content/Buttons/No").gameObject;
			Button noButton = button.GetComponent<Button>();
			noButton.onClick.AddListener(noEvent);
			noButton.onClick.AddListener(destroyMsgBox);

			return true;
		}

		public void notice(string msg) {
			if (msgBox) this.close();

			setupMsgBox(noticeMsgBox, msg);
		}

		public void close() {
			if (!msgBox) return;

			Destroy(msgBox);
			msgBox = null;
		}
	}
}
