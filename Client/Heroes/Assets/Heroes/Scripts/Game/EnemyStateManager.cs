using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public class EnemyStateManager : MonoBehaviour {
		[SerializeField] private bool isInvicible;
		[SerializeField] private float hp = 100;

		private Animator animator;

		private void Start() {
			animator = GetComponent<Animator>();
		}

		private void Update() {
			if(hp <= 0) {
				animator.Play("Die");
			}
		}

		public void TakeDamage(float damage) {
			if (isInvicible) return;

			hp -= damage;
			animator.Play("Take Damage");
		}
	}
}