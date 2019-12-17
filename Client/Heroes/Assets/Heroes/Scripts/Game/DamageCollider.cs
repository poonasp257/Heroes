using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public class DamageCollider : MonoBehaviour {
		private BoxCollider collider;

		public int Damage { get { return 10; } }

		private void Start() {
			collider = GetComponent<BoxCollider>();
			if (collider) collider.enabled = false;
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