using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public class CameraFollow : MonoBehaviour {
		private Transform target;

		private const float CameraMoveSpeed = 120.0f;
				
		private void Start() {
			GameObject player = GameObject.FindGameObjectWithTag("Player");
			if (!player) return;

			target = player.transform.Find("CameraFollow");

			transform.position = target.position;
		}
		
		private void LateUpdate() {
			FollowTarget();
		}

		private void FollowTarget() {
			if (target == null) return;
			
			float step = CameraMoveSpeed * Time.deltaTime;
			transform.position = Vector3.MoveTowards(transform.position, target.position, step);
		}
	}
}