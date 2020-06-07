using UnityEngine;
using UnityEngine.UI;

namespace Heroes {
    public class UIChatBox : MonoBehaviour {
        private float chatBoxWidth;

        [SerializeField] private Text nameText;
        [SerializeField] private Text messageText;

        public void initialize(string name, string message) {
            nameText.text = string.Format("[{0}]:", name);
            messageText.text = message;

            RectTransform rectTransform = this.transform as RectTransform;
            chatBoxWidth = rectTransform.rect.width;
            nameText.rectTransform.sizeDelta = new Vector2(nameText.preferredWidth, 0f);
            messageText.rectTransform.sizeDelta = new Vector2(chatBoxWidth - nameText.preferredWidth, 0f);
        }
    }
}