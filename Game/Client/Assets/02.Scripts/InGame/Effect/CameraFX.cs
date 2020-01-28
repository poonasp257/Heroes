using System.Collections;
using UnityEngine;

namespace Heroes {
	public class CameraFX : MonoBehaviour {
		private Camera camera;

		[Header("Shake FX")]
		private Vector3 startPosition;
		[SerializeField, Range(0, 10)] private float shakeDuration = 1.0f;
		[SerializeField, Range(0, 10)] private float range = 1.0f;

		private void Start() {
			camera = GetComponent<Camera>();
		}

		public void Shake() {
			startPosition = transform.position;
			StartCoroutine("ShakeCamera");
		}
		
		IEnumerator ShakeCamera() {
			float duration = shakeDuration;

			while(true) {
				transform.position = startPosition + range * Random.insideUnitSphere;

				duration -= Time.deltaTime;
				if(duration <= 0) {
					transform.position = startPosition;
					yield break;
				}

				yield return null;
			}
		}
	}
}