using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public class CameraFollow : MonoBehaviour {
		public GameObject cameraFollowObj;
		public float cameraMoveSpeed = 120.0f;
		public float clampAngle = 80.0f;
		public float inputSensitivity = 150.0f;
		public float mouseX;
		public float mouseY;
		private Vector3 rotation;

		// Start is called before the first frame update
		private void Start()
		{
			rotation = transform.localRotation.eulerAngles;
			Cursor.lockState = CursorLockMode.Locked;
			Cursor.visible = false;
		}

		// Update is called once per frame
		void Update()
		{
			mouseX = Input.GetAxis("Mouse X");
			mouseY = Input.GetAxis("Mouse Y");

			rotation.y += mouseX * inputSensitivity * Time.deltaTime;
			rotation.x += mouseY * inputSensitivity * Time.deltaTime;

			rotation.x = Mathf.Clamp(rotation.x, -clampAngle, clampAngle);

			Quaternion localRotation = Quaternion.Euler(rotation.x, rotation.y, 0.0f);
			transform.rotation = localRotation;
		}

		void LateUpdate()
		{
			CameraUpdater();
		}

		void CameraUpdater()
		{
			Transform target = cameraFollowObj.transform;
			float step = cameraMoveSpeed * Time.deltaTime;
			transform.position = Vector3.MoveTowards(transform.position, target.position, step);
		}
	}
}