using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public class CameraFollow : MonoBehaviour {
		[SerializeField] private const float CameraMoveSpeed = 120.0f;
		[SerializeField] private const float ClampAngle = 80.0f;
		[SerializeField] private const float InputSensitivity = 150.0f;

		private Transform target;

		private float mouseX;
		private float mouseY;
		private Vector3 rotation;
		
		private void Start() {
			GameObject player = GameObject.FindGameObjectWithTag("Player");
			if (!player) return;

			target = player.transform.Find("CameraFollow");

			transform.position = target.position;
			rotation = transform.localRotation.eulerAngles;
			
			Cursor.lockState = CursorLockMode.Locked;
			Cursor.visible = false;
		}

		private void Update() {
			RotateCamera();
		}

		private void LateUpdate() {
			FollowTarget();
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

		private void FollowTarget() {
			if (target == null) return;
			
			float step = CameraMoveSpeed * Time.deltaTime;
			transform.position = Vector3.MoveTowards(transform.position, target.position, step);
		}
	}
}