using UnityEngine;
using UnityEngine.UI;

namespace Heroes {
    public class UIPlayerName : MonoBehaviour {
        [SerializeField] private Text familyName;
        [SerializeField] private Text characterName;

        private void Start() {
            var stateManager = GetComponentInParent<PlayerStateManager>();
            familyName.text = stateManager.FamilyName;
            characterName.text = stateManager.info.name;
        }
    }
}