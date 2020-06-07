using UnityEngine;

namespace Heroes {
    public class DamageCollider : MonoBehaviour {
        private CharacterStateManager stateManager = null;

        private void Start() {
            stateManager = GetComponentInParent<CharacterStateManager>();
        }

        private void OnTriggerEnter(Collider other) {
            if(other.tag == "Monster" ||
                other.tag == "Other Player") {
                stateManager.LastTarget = other.GetComponent<CharacterStateManager>();
            }
        }
    }
}