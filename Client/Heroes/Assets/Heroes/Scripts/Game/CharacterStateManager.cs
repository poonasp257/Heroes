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