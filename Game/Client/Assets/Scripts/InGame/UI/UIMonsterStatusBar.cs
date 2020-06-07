using UnityEngine;
using UnityEngine.UI;

namespace Heroes {
	public class UIMonsterStatusBar : UIStatusBar {
		private MonsterStateManager stateManager;

		protected void Start() {
			stateManager = GetComponentInParent<MonsterStateManager>();
			this.initialize((float)stateManager.info.currentHp / (float)stateManager.info.maxHp);
		}

		private void Update() {
			this.updateBar((float)stateManager.info.currentHp / (float)stateManager.info.maxHp);
		}
	}
}