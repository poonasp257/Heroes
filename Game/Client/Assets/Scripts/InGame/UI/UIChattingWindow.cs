using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.UI;

namespace Heroes {
    public class UIChattingWindow : MonoBehaviour, IPointerEnterHandler, IPointerExitHandler {
        private ScrollRect scrollRect = null;
        private Image backgroundImage = null;
        private Color originBackgroundColor;
        private Color disabledBackgroundColor;
        [Range(0.0f, 1.0f), SerializeField] private float backgroundTransparency = 1.0f;

        [SerializeField] private GameObject userChatLogPrefab = null;

        private void Start() {
            scrollRect = GetComponent<ScrollRect>();
            backgroundImage = GetComponent<Image>();

            originBackgroundColor = backgroundImage.color;
            disabledBackgroundColor = originBackgroundColor;
            disabledBackgroundColor.a = backgroundTransparency;

            this.disableChatWindow();
        }
                
        private void updateScrollbar() {
            Canvas.ForceUpdateCanvases();
            scrollRect.content.GetComponent<VerticalLayoutGroup>().CalculateLayoutInputVertical();
            scrollRect.content.GetComponent<ContentSizeFitter>().SetLayoutVertical();
            scrollRect.verticalNormalizedPosition = 0;
        }

        private void enableChatWindow() {
            scrollRect.enabled = true;
            scrollRect.verticalScrollbar.gameObject.SetActive(true);
            backgroundImage.color = originBackgroundColor;
        }

        private void disableChatWindow() {
            scrollRect.enabled = false;
            scrollRect.verticalScrollbar.gameObject.SetActive(false);
            backgroundImage.color = disabledBackgroundColor;
        }

        public void OnPointerEnter(PointerEventData pointerEvent) {
            this.enableChatWindow();
        }

        public void OnPointerExit(PointerEventData pointerEvent) {
            this.disableChatWindow();
        }

        public void createUserChatBox(string name, string message) {
            var chatBox = Instantiate(userChatLogPrefab, scrollRect.content);
            var chatBoxScript = chatBox.GetComponent<UIChatBox>();
            chatBoxScript.initialize(name, message);
            this.updateScrollbar();
        }
    }
}