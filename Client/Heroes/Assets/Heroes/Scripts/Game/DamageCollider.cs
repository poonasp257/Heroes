using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public class DamageCollider : MonoBehaviour {
		private BoxCollider collider;

		private void Start() {
			collider = GetComponent<BoxCollider>();
			if (collider) collider.enabled = false;
		}

		private void OnTriggerEnter(Collider other) {
			EnemyStateManager enemyState = other.GetComponent<EnemyStateManager>();

			if (enemyState == null) return;

			enemyState.TakeDamage(25);
		}

		public void Enable() {
			if (collider == null) return;

			collider.enabled = true;
		}

		public void Disable() {
			if (collider == null) return;
			
			collider.enabled = false;
		}
	}
}