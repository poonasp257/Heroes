using System.Collections;
using UnityEngine;
using UnityEngine.UI;

namespace Heroes {
    public class InformHandler : MonoBehaviour {
        private Text message;
        private float displayTimer = 0f;
        [SerializeField] private float displayerDurationTime = 5.0f;
        [SerializeField] private float fadeSpeed = 2.0f;

        private void Start() {
            message = GetComponent<Text>();
        }

        private void Update() {
            if (message.color.a <= 0f) return;

            displayTimer += Time.deltaTime;
            if (displayTimer < displayerDurationTime) return;

            displayTimer = 0f;
            StartCoroutine(FadeOutMessage());
        }

        private IEnumerator FadeInMessage() {
            Color color = this.message.color;
            color.a = 0f;
            this.message.color = Color.clear;

            while (color.a < 1.0f) {
                color.a += Time.deltaTime * fadeSpeed;
                message.color = color;

                yield return null;
            }
        }

        private IEnumerator FadeOutMessage() {
            Color color = this.message.color;
            while (color.a > 0.0f) {
                color.a -= Time.deltaTime * fadeSpeed;
                message.color = color;

                yield return null;
            }
        }

        public void displayMessage(string message) {
            this.message.text = message;
            StartCoroutine(FadeInMessage());
        }
    }
}