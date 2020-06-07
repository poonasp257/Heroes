using UnityEngine;
using UnityEngine.UI;

namespace Heroes {
    public class UIMonsterName : MonoBehaviour {
        [SerializeField] private Text name;

        private void Start() {
            var stateManager = GetComponentInParent<MonsterStateManager>();
            name.text = stateManager.info.name;
        }
    }
}
