using System;
using System.Collections;
using UnityEngine;

namespace Heroes {
    public abstract class CharacterStateManager : MonoBehaviour {
		protected Animator animator = null;
		protected Coroutine actionCoroutine = null;

		public bool IsGrounded {
			get {
				return Physics.Raycast(transform.position, Vector3.down, 0.5f);
			}
		}

		public bool IsInAction { get { return actionCoroutine != null; } }

		public CharacterStateManager LastTarget { get; set; }

		protected virtual void Start() {
			animator = GetComponentInChildren<Animator>();
		}

		protected void OnDisable() {
			actionCoroutine = null;
		}

		protected virtual IEnumerator ExecuteAction(string actionName) {
			animator.SetTrigger(actionName);
			while (!animator.GetCurrentAnimatorStateInfo(0).IsName(actionName)) {
				yield return null;
			}

			while (!animator.IsInTransition(0)) {
				yield return null;
			}

			actionCoroutine = null;
		}

		public virtual void forcedExecuteAction(ActionType type) {
			if (animator == null) {
				animator.SetTrigger(type.ToString());
				return;
			}

			if (actionCoroutine != null) {
				StopCoroutine(actionCoroutine);
			}

			this.enableRootMotion();
			actionCoroutine = StartCoroutine(ExecuteAction(type.ToString()));
		}

		public virtual void executeAction(ActionType type) {
			if (animator == null) {
				animator.SetTrigger(type.ToString());
				return;
			}

			if (actionCoroutine != null) return;

			this.enableRootMotion();
			actionCoroutine = StartCoroutine(ExecuteAction(type.ToString()));
		}

		public void disableRootMotion() {
			animator.applyRootMotion = false;
		}

		public void enableRootMotion() {
			animator.applyRootMotion = true;
		}
	}
}