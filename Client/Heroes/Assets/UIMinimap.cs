using UnityEngine;
using UnityEngine.UI;

namespace Heroes {
	public class UIMinimap : MonoBehaviour {
		private CharacterStateManager characterState;

		private Text location;

		private void Start() {
			GameObject playerManagerObj = GameObject.Find("Player Manager");
			if(!playerManagerObj) {
				Debug.Log("Player Manager object doesn't exist");
				return;
			}

			PlayerManager playerManager = playerManagerObj.GetComponent<PlayerManager>();
			if (!playerManagerObj) {
				Debug.Log("Player Manager doesn't exist");
				return;
			}

			Transform locationTransform = transform.Find("Location");
			if(!locationTransform) {
				Debug.Log("Location Object doesn't exist");
				return;
			}

			location = locationTransform.GetComponent<Text>();
			if(!locationTransform) {
				Debug.Log("Location doesn't exist");
				return;
			}

			characterState = playerManager.getCharacterState(PlayerData.Instance.AccountId);
		}

		private void Update() {
			if (!characterState) {
				Debug.Log("Character State Manager doesn't exist");
				return;
			}

			location.text = characterState.Info.location;
		}
	}
}