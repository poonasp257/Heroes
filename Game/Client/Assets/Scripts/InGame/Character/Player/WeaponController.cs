using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public class WeaponController : MonoBehaviour {
		private List<MeleeWeaponTrail> trails = new List<MeleeWeaponTrail>();
		private List<BoxCollider> weaponColliders = new List<BoxCollider>();

		private void Start() {
			trails.AddRange(GetComponentsInChildren<MeleeWeaponTrail>());
			if (this.gameObject.tag == "Player") {
				weaponColliders.AddRange(GetComponentsInChildren<BoxCollider>());
				foreach (var collider in weaponColliders) {
					collider.gameObject.AddComponent<DamageCollider>();
				}
			}

			disableWeaponColliders();
		}
		
		public void enableWeaponColliders() {
			foreach(var trail in trails) {
				trail.Emit = true;
			}

			foreach (var collider in weaponColliders) {
				collider.enabled = true;
			}
		}

		public void disableWeaponColliders() {
			foreach (var trail in trails) {
				trail.Emit = false;
			}

			foreach (var collider in weaponColliders) {
				collider.enabled = false;
			}
		}
	}
}