using UnityEngine.UI;
using UnityEngine.Events;
using UnityEngine.EventSystems;

namespace Heroes {
    public class UIButton : Button {
        public UnityEvent onSubmit = new UnityEvent();

        public void registerAction(UnityAction action) {
            onClick.AddListener(action);
            onSubmit.AddListener(action);
        }

        public void unregisterAction(UnityAction action) {
            onClick.RemoveListener(action);
            onSubmit.RemoveListener(action);
        }

        public override void OnSubmit(BaseEventData eventData) {
            onSubmit?.Invoke();
        }
    }
}