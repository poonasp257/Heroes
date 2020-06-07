using UnityEngine;

namespace Heroes {
    [ExecuteInEditMode]
    public class UICirclePlacement : MonoBehaviour {
        private RectTransform rectTransform = null;
        [SerializeField] private float radius = 1.0f;

        private void Awake() {
            rectTransform = GetComponent<RectTransform>();
        }

        private void Start() {
            Vector2 center = rectTransform.anchoredPosition;
            float angleOffset = 2 * Mathf.PI / transform.childCount;
            for (int i = 0; i < transform.childCount; ++i) {
                float angle = angleOffset * (i + 1);
                float x = radius * Mathf.Cos(angle) + center.x;
                float y = radius * Mathf.Sin(angle) + center.y;
                var child = transform.GetChild(i).GetComponent<RectTransform>();
                child.anchoredPosition = new Vector2(x, y);
            }
        }
    }
}