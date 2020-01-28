using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public class CameraCollision : MonoBehaviour {
		[SerializeField] private const float MinDistance = 1.0f;
		[SerializeField] private const float MaxDistance = 4.0f;
		[SerializeField] private const float Smooth = 10.0f;
		[SerializeField] private const float HitDistanceAdjust = 0.8f;
		
		private float distance;
		private Vector3 dir;

		private void Start() {
			distance = transform.localPosition.magnitude;
			dir = transform.localPosition.normalized; 
		}

		private void Update() {
			float distance = transform.localPosition.magnitude;			
			Vector3 desiredCameraPos = transform.parent.TransformPoint(dir * MaxDistance);
			RaycastHit hit;

			if (Physics.Linecast(transform.parent.position, desiredCameraPos, out hit)) {
				distance = Mathf.Clamp(( hit.distance * HitDistanceAdjust ), MinDistance, MaxDistance);
			}
			else distance = MaxDistance;

			transform.localPosition = Vector3.Lerp(transform.localPosition, dir * distance, Time.deltaTime * Smooth);
		}

		private void CalculateDistance() {

		}
	}
}