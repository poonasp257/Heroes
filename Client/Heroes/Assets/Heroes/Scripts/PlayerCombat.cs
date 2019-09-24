using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public class PlayerCombat : MonoBehaviour {
		private Animator animator;
		private PlayerStateManager stateManager;

		private void Start() {
			animator = GetComponent<Animator>();
			stateManager = GetComponent<PlayerStateManager>();
		}

		private void Update() {
			Attack();
		}

		private void Attack() {
			if (Input.GetMouseButtonDown(0)) {
				animator.CrossFade("normal_attack_1", 0.2f);
			}
			else if(Input.GetMouseButtonDown(1)) {
				animator.CrossFade("smash_attack_3", 0.2f);
			}
		}
	}
}