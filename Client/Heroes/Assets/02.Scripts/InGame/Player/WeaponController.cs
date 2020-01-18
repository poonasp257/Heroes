using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public class WeaponController : MonoBehaviour {
		private MeleeWeaponTrail trail;
		private DamageCollider[] colliders;

		private void Start() {
			trail = GetComponentInChildren<MeleeWeaponTrail>();
			colliders = GetComponentsInChildren<DamageCollider>();

			DisableDamageColliders();
		}
		
		public void EnableDamageColliders() {
			if (trail) trail.Emit = true;

			foreach (DamageCollider damageCollider in colliders) {
				damageCollider.Enable();
			}
		}

		public void DisableDamageColliders() {
			if (trail) trail.Emit = false;

			foreach (DamageCollider damageCollider in colliders) {
				damageCollider.Disable();
			}
		}
	}
}