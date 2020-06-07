using System.Collections;
using UnityEngine;
using UnityEngine.UI;

namespace Heroes {
    public class UIStatusBar : MonoBehaviour {
        private Color normalColor;

        private const float RevertSpeed = 1.5f;
        [SerializeField] private Image statusBar;
        [SerializeField] private Color hitColor;

        protected virtual void Awake() {
            normalColor = statusBar.color;
        }

        private IEnumerator RevertToNormalColor() {
            Vector3 targetColor = new Vector3(normalColor.r, normalColor.g, normalColor.b);

            while (true) {
                Vector3 currentColor = new Vector3(statusBar.color.r, statusBar.color.g, statusBar.color.b);
                currentColor = Vector3.MoveTowards(currentColor, targetColor, Time.deltaTime * RevertSpeed);
                statusBar.color = new Color(currentColor.x, currentColor.y, currentColor.z);
                if(currentColor == targetColor) {
                    yield break;
                }

                yield return null;
            }
        } 

        public void initialize(float statusPoint) {
            statusBar.fillAmount = statusPoint;
        }

        public bool updateBar(float statusPoint) {
            if (statusBar.fillAmount == statusPoint) return false;

            statusBar.color = hitColor;
            statusBar.fillAmount = statusPoint;
            StartCoroutine(RevertToNormalColor());
            return true;
        }
    }
}
