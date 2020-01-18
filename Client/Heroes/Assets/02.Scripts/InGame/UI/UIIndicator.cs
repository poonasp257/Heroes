using UnityEngine;
using UnityEngine.UI;

namespace Heroes {
	public class UIIndicator : MonoBehaviour {
		private const float borderWidth = 4.0f;

		private Text figure;

		private RectTransform rectTransform;
		private Vector2 originPosition;

		private float barWidth;
		private Image barImage;

		[SerializeField] private GameObject bar;

		public float CurrentFigure { get; set; }
		public float MaxFigure { get; set; }

		private void Start() {
			figure = GetComponentInChildren<Text>();
			
			barImage = bar.GetComponent<Image>();
			RectTransform barTransform = bar.GetComponent<RectTransform>();

			rectTransform = this.GetComponent<RectTransform>();
			originPosition = rectTransform.anchoredPosition;

			barWidth = barTransform.rect.width - borderWidth * 2;
		}

		private void Update() {
			updateIndicator();
			updateFigure();
		}

		private void updateIndicator() {
			Vector2 currentPosition = originPosition;
			currentPosition.x += barWidth * barImage.fillAmount;

			rectTransform.anchoredPosition = currentPosition;
		}

		private void updateFigure() {
			figure.text = CurrentFigure + "/" + MaxFigure;
		}
	}
}