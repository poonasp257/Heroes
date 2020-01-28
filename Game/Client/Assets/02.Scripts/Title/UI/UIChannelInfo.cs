using System;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;
using UnityEngine.SceneManagement;

namespace Heroes {
	public class UIChannelInfo : MonoBehaviour, IScrollHandler {
		private Text ChannelName;
		private Text traffic;

		private ScrollRect scrollRect;

		public UInt16 ID { get; set; }

		public string Name {
			get {
				return ChannelName.text;
			}
			set {
				ChannelName.text = value;
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
			ChannelName = transform.Find("Channel Name").GetComponent<Text>();
			traffic = transform.Find("Traffic").GetComponent<Text>();
		}

		private void Start() {
			scrollRect = GetComponentInParent<ScrollRect>();
		}

		public void OnConnectButtonClick() {
			PlayerData.Instance.ChannelId = ID;
			SceneManager.LoadScene("Select");
		}

		public void OnScroll(PointerEventData eventData) {
			scrollRect.OnScroll(eventData);
		}
	}
}