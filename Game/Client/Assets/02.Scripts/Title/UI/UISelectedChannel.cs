using UnityEngine;
using UnityEngine.UI;

namespace Heroes {
	public class UISelectedChannel : MonoBehaviour {
		[SerializeField] private Text channelText;

		public bool IsSelected { 
			get { 
				return !string.IsNullOrWhiteSpace(channelText.text);
			} 
		}

		private void Start() {
			channelText.text = "";
		}

		public void selectChannel(string channelName) {
			channelText.text = channelName;
		}

		public void deselectChannel() {
			channelText.text = "";
		}
	}
}