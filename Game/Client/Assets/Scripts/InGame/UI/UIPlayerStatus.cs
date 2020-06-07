using System;
using UnityEngine;
using UnityEngine.UI;

namespace Heroes { 
	public class UIPlayerStatus : MonoBehaviour {
		private PlayerStateManager stateManager;

		[SerializeField] private UIStatusBar hpBar;
		[SerializeField] private UIStatusBar mpBar;
		[SerializeField] private UIIndicator hpBarIndicator;
		[SerializeField] private UIIndicator mpBarIndicator;	
		[SerializeField] private Text level;
		[SerializeField] private Text exp;

		private void Start()  {
			var player = GameObject.FindWithTag("Player");
			if (player == null) throw new Exception("Player not found");

			stateManager = player.GetComponent<PlayerStateManager>();

			hpBar.initialize((float)stateManager.info.currentHp / (float)stateManager.info.maxHp);
			mpBar.initialize((float)stateManager.info.currentMp / (float)stateManager.info.maxMp);
		}

		private void Update() {
			UInt32 playerLevel = stateManager.info.level;
			float goalExp = 100 * playerLevel * playerLevel;
			level.text = playerLevel.ToString();
			exp.text = (((float)stateManager.info.exp / goalExp) * 100).ToString("F3") + "%";
			
			updateHealthPoint();
			updateManaPoint();
		}

		private void updateHealthPoint() {
			hpBar.updateBar((float)stateManager.info.currentHp / (float)stateManager.info.maxHp);
			hpBarIndicator.CurrentFigure = stateManager.info.currentHp;
			hpBarIndicator.MaxFigure = stateManager.info.maxHp;
		}
		
		private void updateManaPoint() {
			mpBar.updateBar((float)stateManager.info.currentMp / (float)stateManager.info.maxMp);
			mpBarIndicator.CurrentFigure = stateManager.info.currentMp;
			mpBarIndicator.MaxFigure = stateManager.info.maxMp;
		}
	}
}