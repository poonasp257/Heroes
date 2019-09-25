using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public class CameraFollow : MonoBehaviour {
		[SerializeField] private const float CameraMoveSpeed = 120.0f;
		[SerializeField] private const float ClampAngle = 80.0f;
		[SerializeField] private const float InputSensitivity = 150.0f;

		private float mouseX;
		private float mouseY;
		private Vector3 rotation;
		
		public GameObject targetObj;
		
		private void Start() {
			rotation = transform.localRotation.eulerAngles;
			Cursor.lockState = CursorLockMode.Locked;
			Cursor.visible = false;
		}

		private void Update() {
			RotateCamera();
		}

		private void LateUpdate() {
			FollowObject();
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

		private void FollowObject() {
			Transform targetTransfrom = targetObj.transform;
			float step = CameraMoveSpeed * Time.deltaTime;
			transform.position = Vector3.MoveTowards(transform.position, targetTransfrom.position, step);
		}
	}
}