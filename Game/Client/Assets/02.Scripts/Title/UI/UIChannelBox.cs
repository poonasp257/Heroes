using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;
using UnityEngine.Events;

namespace Heroes {
	public class UIChannelBox : MonoBehaviour, IScrollHandler {
		private Text channelName;
		private ScrollRect scrollRect;

		public UnityAction onClickEvent { get; set; }

		private void Start() {
			channelName = transform.Find("Channel Name").GetComponent<Text>();
			channelName.text = gameObject.name;

			scrollRect = GetComponentInParent<ScrollRect>();
		}

		public void onClick() {
			onClickEvent?.Invoke();
		}

		public void OnScroll(PointerEventData eventData) {
			scrollRect?.OnScroll(eventData);
		}
	}
}