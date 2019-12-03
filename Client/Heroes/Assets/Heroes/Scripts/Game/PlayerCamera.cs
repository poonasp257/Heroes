using UnityEngine;

namespace Heroes {
	public class PlayerCamera : MonoBehaviour {
		private float mouseX;
		private float mouseY;
		private Vector3 rotation;

		[SerializeField] private const float ClampAngle = 80.0f;
		[SerializeField] private const float InputSensitivity = 150.0f;

		private void Start() {
			rotation = transform.localRotation.eulerAngles;

			Cursor.lockState = CursorLockMode.Locked;
			Cursor.visible = false;
		}

		private void Update() {
			RotateCamera();
		}

		private void RotateCamera() {			
			mouseX = Input.GetAxis("Mouse X");
			mouseY = Input.GetAxis("Mouse Y");

			rotation.y += mouseX * InputSensitivity * Time.deltaTime;
			rotation.x += mouseY * InputSensitivity * Time.deltaTime;

			rotation.x = Mathf.Clamp(rotation.x, -ClampAngle, ClampAngle);

			Quaternion localRotation = Quaternion.Euler(rotation.x, rotation.y, 0.0f);
			transform.rotation = localRotation;
		}
	}
}