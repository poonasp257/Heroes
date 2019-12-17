using UnityEngine;

namespace Heroes {
	public class CharacterStateManager : MonoBehaviour {
		private Animator animator;

		private TextMesh familyName;
		private TextMesh characterName;

		public CharacterInfo Info { get; set; } 

		private void Start() {
			animator = GetComponent<Animator>();

			Transform names = transform.Find("Names");
			familyName = names.Find("Family Name").GetComponent<TextMesh>();
			characterName = names.Find("Character Name").GetComponent<TextMesh>();

			familyName.text = Info.familyName;
			characterName.text = Info.characterName;
		}

		private void Attack() {
			animator.SetInteger("attackStep", 0);
			animator.SetTrigger("Combat");
		}

		private void SmashAttack() {
			animator.SetBool("RButton", true);
		}

		private void Roll() {
			animator.SetTrigger("Roll");
		}

 		public void UpdateTransform(CharacterMovement movement) {
			animator.SetFloat("moveAmount", movement.moveAmount);
			transform.position = movement.position;
			transform.rotation = Quaternion.Euler(movement.rotation);
		}

		public void ExecuteAction(ActionType type) {
			switch(type)  {
				case ActionType.WeakAttack: Attack();  break;
				case ActionType.SmashAttack: SmashAttack(); break;
				case ActionType.Roll: Roll(); break;
			}
		}
	}
}