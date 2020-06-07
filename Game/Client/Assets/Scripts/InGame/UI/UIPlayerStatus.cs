using UnityEngine;
using UnityEngine.UI;

namespace Heroes { 
	public class UIPlayerStatus : MonoBehaviour {
		private CharacterStateManager characterState;

		private Text level;
		private Text exp;

		private Image hpBarImage;
		private Image mpBarImage;
		private UIIndicator hpBarIndicator;
		private UIIndicator mpBarIndicator;	

		private void Start()  {
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

			characterState = playerManager.getCharacterState(AccountData.Instance.accessKey);

			level = transform.Find("Panel/Level").gameObject.GetComponent<Text>();
			exp = transform.Find("Panel/EXP").gameObject.GetComponent<Text>();

			Transform hp = transform.Find("HP");
			Transform mp = transform.Find("MP");

			hpBarImage = hp.transform.Find("Bar").GetComponent<Image>();
			mpBarImage = mp.transform.Find("Bar").GetComponent<Image>();

			hpBarIndicator = hp.transform.Find("Indicator").GetComponent<UIIndicator>();
			mpBarIndicator = mp.transform.Find("Indicator").GetComponent<UIIndicator>();
		}

		private void Update() {
			if (characterState == null) return;

			level.text = characterState.Info.level.ToString();
			exp.text = characterState.Info.exp.ToString("F3") + "%";

			updateHPUI();
			updateMPUI();
		}

		private void updateHPUI() {
			CharacterInfo playerInfo = characterState.Info;
			hpBarImage.fillAmount = (float)playerInfo.currentHp / (float)playerInfo.maxHp;

			hpBarIndicator.CurrentFigure = playerInfo.currentHp;
			hpBarIndicator.MaxFigure = playerInfo.maxHp;
		}
		
		private void updateMPUI() {
			CharacterInfo playerInfo = characterState.Info;
			mpBarImage.fillAmount = (float)playerInfo.currentMp / (float)playerInfo.maxMp;

			mpBarIndicator.CurrentFigure = playerInfo.currentMp;
			mpBarIndicator.MaxFigure = playerInfo.maxMp;
		}
	}
}