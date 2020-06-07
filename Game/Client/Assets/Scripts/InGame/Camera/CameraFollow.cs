using System;
using UnityEngine;

namespace Heroes {
	public class CameraFollow : MonoBehaviour {
		private Transform target;

		[SerializeField] private float CameraMoveSpeed = 120.0f;

		private void Start() {
			var player = GameObject.FindGameObjectWithTag("Player");
			if (player == null) throw new Exception("Player not found");

			target = createFollowTarget(player);
			transform.position = target.position; 
		}
		
		private void LateUpdate() {
			if(target != null) followTarget();
		}

		private Transform createFollowTarget(GameObject parentObj) {
			var targetObj = new GameObject("Camera Follow");
			targetObj.transform.parent = parentObj.transform;
			targetObj.transform.localPosition = new Vector3(0, 2.5f, 0);
			targetObj.transform.localRotation = Quaternion.identity;
			return targetObj.transform;
		}

		private void followTarget() {			
			float step = CameraMoveSpeed * Time.deltaTime;
			transform.position = Vector3.MoveTowards(transform.position, target.position, step);
		}
	}
}