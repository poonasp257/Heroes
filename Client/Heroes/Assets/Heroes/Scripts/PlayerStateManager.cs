using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public class PlayerStateManager : MonoBehaviour {
		private Animator animator;
		
		public bool InAction { get; set; }

		private void Start() {
			Initialize();
		}

		private void Update() {
			Tick();
		}

		private void Initialize() {
			animator = GetComponent<Animator>();
			InAction = false;
		}

		private void Tick() {
			InAction = !animator.GetBool("canMove");
		}
	}
}