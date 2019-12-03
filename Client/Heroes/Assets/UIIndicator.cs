using UnityEngine;
using UnityEngine.UI;

namespace Heroes {
	public class UIIndicator : MonoBehaviour {
		private const float borderWidth = 4.0f;

		private Text figure;

		private Vector3 originPosition;

		private float barWidth;
		private Image barImage;

		[SerializeField] private GameObject bar;

		public float CurrentFigure { get; set; }
		public float MaxFigure { get; set; }

		private void Start() {
			figure = GetComponentInChildren<Text>();

			originPosition = this.transform.position;

			barImage = bar.GetComponent<Image>();
			RectTransform barTransform = bar.GetComponent<RectTransform>();

			float adjust = Screen.width / Screen.currentResolution.width;
			barWidth = (barTransform.rect.width * adjust) - borderWidth * 2;
		}

		private void Update() {
			updateIndicator();
			updateFigure();
		}

		private void updateIndicator() {
			Vector3 currentPosition = originPosition;
			currentPosition.x += barWidth * barImage.fillAmount;

			this.transform.position = currentPosition;
		}

		private void updateFigure() {
			figure.text = CurrentFigure + "/" + MaxFigure;
		}
	}
}