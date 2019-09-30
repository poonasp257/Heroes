using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public class WeaponController : MonoBehaviour {
		[SerializeField] private DamageCollider[] colliders;

		private void Start() {
			colliders = GetComponentsInChildren<DamageCollider>();
			DisableDamageColliders();
		}

		public void EnableDamageColliders() {
			foreach(DamageCollider damageCollider in colliders) {
				damageCollider.Enable();
			}
		}

		public void DisableDamageColliders() {
			foreach(DamageCollider damageCollider in colliders) {
				damageCollider.Disable();
			}
		}
	}
}