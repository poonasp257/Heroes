using System;
using UnityEngine;

namespace Heroes {
	public class PlayerStateManager : CharacterStateManager {
		public string FamilyName { get; set; }
		public CharacterInfo info;

		public bool IsDead { get { return info.currentHp <= 0; } }

		protected override void Start() {
			base.Start();

			if(IsDead) this.die();
		}

		public void die() {
			info.currentHp = 0;
			animator.SetTrigger("Die");
		}
	}
}