using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public class DamageCollider : MonoBehaviour {
		private void OnTriggerEnter(Collider other) {
			EnemyStateManager enemyState = other.GetComponent<EnemyStateManager>();

			if (enemyState == null) return;

			enemyState.TakeDamage(25);
		}
	}
}