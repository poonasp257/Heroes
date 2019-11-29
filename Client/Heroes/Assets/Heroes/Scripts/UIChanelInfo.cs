using System;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;
using UnityEngine.SceneManagement;

namespace Heroes {
	public class UIChanelInfo : MonoBehaviour, IScrollHandler {
		private Text chanelName;
		private Text traffic;

		private ScrollRect scrollRect;

		public UInt16 ID { get; set; }

		public string Name {
			get {
				return chanelName.text;
			}
			set {
				chanelName.text = value;
			}
		}

		public Int32 Traffic {
			get {
				return Int32.Parse(traffic.text);
			}
			set {
				traffic.text = value.ToString();
			}
		}

		private void Awake() {
			chanelName = transform.Find("Chanel Name").GetComponent<Text>();
			traffic = transform.Find("Traffic").GetComponent<Text>();
		}

		private void Start() {
			scrollRect = GetComponentInParent<ScrollRect>();
		}

		public void OnConnectButtonClick() {
			PlayerData.Instance.ChanelId = ID;
			SceneManager.LoadScene("Select");
		}

		public void OnScroll(PointerEventData eventData) {
			scrollRect.OnScroll(eventData);
		}
	}
}