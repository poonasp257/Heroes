using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;
using UnityEngine.Events;

namespace Heroes {
	public class UIChannelBox : MonoBehaviour, IScrollHandler {
		private ScrollRect scrollRect;

		[SerializeField] private Text channelName = null;

		public UnityAction onClickAction { get; set; }
		public UnityAction onConnectAction { get; set; }

		private void Start() {
			channelName.text = this.gameObject.name;
			scrollRect = GetComponentInParent<ScrollRect>();
		}

		public void OnClick() {
			onClickAction?.Invoke();
		}

		public void OnConnect() {
			onConnectAction?.Invoke();
		}
						
		public void OnScroll(PointerEventData eventData) {
			scrollRect?.OnScroll(eventData);
		}
	}
}