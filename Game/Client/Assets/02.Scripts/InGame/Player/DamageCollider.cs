using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public class DamageCollider : MonoBehaviour {
		private BoxCollider damageCollider;

		public int Damage { get { return 10; } }

		private void Start() {
			damageCollider = GetComponent<BoxCollider>();
			if (damageCollider) damageCollider.enabled = false;
		}

		public void Enable() {
			if (damageCollider == null) return;

			damageCollider.enabled = true;
		}

		public void Disable() {
			if (damageCollider == null) return;

			damageCollider.enabled = false;
		}
	}
}