using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public class MonsterAI : MonoBehaviour {
		private MonsterController controller;

		private void Start() {
			controller = GetComponentInParent<MonsterController>();
		}

		private void OnTriggerEnter(Collider collider) {
			if (collider.tag == "Player") {
				controller.setTarget(collider.gameObject);
			}
		}
	}
}