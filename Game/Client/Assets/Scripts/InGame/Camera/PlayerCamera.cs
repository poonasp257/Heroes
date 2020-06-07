using UnityEngine;

namespace Heroes {
	public class PlayerCamera : MonoBehaviour {
		private bool enabledRotating = false;
		private Vector3 currentRotation;

		[SerializeField] private float ClampAngle = 80.0f;
		[SerializeField] private float InputSensitivity = 150.0f;

		private void Start() {
			currentRotation = transform.localRotation.eulerAngles;

			ShowCursor();
			EnabledInput = true;
		}

		public static bool EnabledCursor { 
			get { return Cursor.visible; }
		}

		public static bool EnabledInput { get; set;	}

		private void Update() {
			if (!EnabledCursor || enabledRotating) {
				processInput();
			}

			if (!EnabledInput) return;

			if(Input.GetMouseButtonDown(1) && EnabledCursor) {
				HideCursor();
				enabledRotating = true;
			}
			else if(Input.GetMouseButtonUp(1) && enabledRotating) {
				ShowCursor();
				enabledRotating = false;
			}
						
			if (Input.GetButtonDown("Cursor")) {
				if (EnabledCursor) {
					HideCursor();
					return;
				}
				
				ShowCursor();
			}
		}
		
		private void processInput() {
			float mouseX = Input.GetAxis("Mouse X");
			float mouseY = -Input.GetAxis("Mouse Y");
			currentRotation.y += mouseX * InputSensitivity * Time.deltaTime;
			currentRotation.x += mouseY * InputSensitivity * Time.deltaTime;
			currentRotation.x = Mathf.Clamp(currentRotation.x, -ClampAngle, ClampAngle);

			Quaternion localRotation = Quaternion.Euler(currentRotation.x, currentRotation.y, 0.0f);
			transform.rotation = localRotation;
		}

		public static void ShowCursor() {
			Cursor.lockState = CursorLockMode.None;
			Cursor.visible = true;
		}

		public static void HideCursor() {
			Cursor.lockState = CursorLockMode.Locked;
			Cursor.visible = false;
		}
	}
}