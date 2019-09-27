using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public class PlayerCombat : MonoBehaviour {
		private Animator animator;
		private PlayerStateManager stateManager;

		private const float MaxComboDelay = 0.4f;

		[SerializeField] private int countOfLeftAttack;
		[SerializeField] private float lastAttackTime;

		private void Start() {
			Initialize();
		}

		private void Update() {
			ProcessInput();
			Tick();
		}

		private void Initialize() {
			animator = GetComponent<Animator>();
			stateManager = GetComponent<PlayerStateManager>();

			lastAttackTime = 0.0f;
			countOfLeftAttack = 0;
		}

		private void ProcessInput() {
			if (stateManager.InAction) return;

			if (Input.GetButtonDown("Weak Attack")) WeakAttack();
			else if (Input.GetButtonDown("Smash Attack")) SmashAttack();
		}

		private void Tick() {
			if (stateManager.InAction) { 
				lastAttackTime = Time.time;
				return;
			}

			if (Time.time - lastAttackTime > MaxComboDelay) {
				countOfLeftAttack = 0;
			}
		}

		private void WeakAttack() {
			string targetAnimation = null;

			switch(countOfLeftAttack) {
				case 0: targetAnimation = "weak_attack_1"; break;
				case 1: targetAnimation = "weak_attack_2"; break;
				case 2: targetAnimation = "weak_attack_3"; break;
				case 3: targetAnimation = "weak_attack_4"; break;
			}

			if (targetAnimation == null) return;

			animator.CrossFade(targetAnimation, 0.2f);
			stateManager.InAction = true;
			++countOfLeftAttack;
		}

		private void SmashAttack() {
			string targetAnimation = null;

			switch (countOfLeftAttack)
			{
				case 1: targetAnimation = "smash_attack_1"; break;
				case 2: targetAnimation = "smash_attack_2"; break;
				case 3: targetAnimation = "smash_attack_3"; break;
				case 4: targetAnimation = "smash_attack_4"; break;
			}

			if (targetAnimation == null) return;

			animator.CrossFade(targetAnimation, 0.2f);
			stateManager.InAction = true;
			countOfLeftAttack = 0;
		}
	}
}