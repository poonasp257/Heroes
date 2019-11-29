using UnityEngine;

namespace Heroes {
	public class CharacterStateManager : MonoBehaviour {
		private Animator animator;

		public CharacterInfo Info { get; set; } 

		private void Start() {
			animator = GetComponent<Animator>();
		}

		public void UpdateTransform(CharacterMovement movement) {
			animator.SetFloat("moveAmount", movement.moveAmount);
			transform.position = movement.position;
			transform.rotation = Quaternion.Euler(movement.rotation);
		}

		public void ExecuteAction(ActionType type) {
			switch(type)  {
				case ActionType.WeakAttack: break;
				case ActionType.SmashAttack: break;
				case ActionType.Roll: break;
			}
		}
	}
}