using UnityEngine;

namespace Heroes {
	public class CameraCollision : MonoBehaviour {
		private float zoom;

		[SerializeField] private float minDistance = 1.0f;
		[SerializeField] private float maxDistance = 4.0f;
		[SerializeField] private float sensitivity = 1.0f;
		[SerializeField] private float smooth = 10.0f;

		private void Awake() {
			zoom = maxDistance;
		}

		private void LateUpdate() {
			processInput();
			
			Vector3 dir = transform.localPosition.normalized;
			Vector3 movePos = calculateMoveTo(dir);
			transform.localPosition = Vector3.Lerp(transform.localPosition, movePos, Time.deltaTime * smooth);
		}
		
		private void processInput() {
			float mouseWheel = -Input.GetAxis("Mouse ScrollWheel");
			zoom += mouseWheel * sensitivity;
			zoom = Mathf.Clamp(zoom, minDistance, maxDistance);
		}

		private Vector3 calculateMoveTo(Vector3 dir) {
			float distance = zoom;
			Vector3 desiredCameraPos = transform.parent.TransformPoint(dir * zoom);
			RaycastHit hit;
			if (Physics.Linecast(transform.parent.position, desiredCameraPos, out hit)) {
				distance = Mathf.Clamp(hit.distance, minDistance, zoom);
			}

			return dir * distance;
		}
	}
}