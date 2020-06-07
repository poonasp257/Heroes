using System;
using UnityEngine;
using UnityEngine.UI;

namespace Heroes {
    public class UITargetInformation : MonoBehaviour {
        private PlayerStateManager playerStateManager = null;
        private CharacterStateManager targetStateManager = null;

        private float displayTimer = 0f;
        private const float DisplayTime = 10f;

        [SerializeField] private Text targetName;
        [SerializeField] private UIStatusBar hpBar;

        private void Start() {
            var player = GameObject.FindWithTag("Player");
            if (player == null) throw new Exception("Player not found");

            playerStateManager = player.GetComponent<PlayerStateManager>();
        }

        private void Update() {
            if (playerStateManager.LastTarget == null) return;

            var lastTarget = playerStateManager.LastTarget.gameObject;
            if(!lastTarget.activeSelf) {
                this.hideInformation();
                playerStateManager.LastTarget = null;
                targetStateManager = null;
                return;
            }

            this.showInformation();
            this.updateTarget();

            if(targetStateManager == null) {
                this.hideInformation();
            }

            displayTimer += Time.deltaTime;
            if(displayTimer >= DisplayTime) {
               this.hideInformation();
                playerStateManager.LastTarget = null;
                targetStateManager = null;
            }
        }

        private void showInformation() {
            targetName.gameObject.SetActive(true);
            hpBar.gameObject.SetActive(true);
        }

        private void hideInformation() {
            displayTimer = 0f;
            targetName.gameObject.SetActive(false);
            hpBar.gameObject.SetActive(false);
        }


        private void setTargetToPlayer(PlayerStateManager target) {
            this.targetStateManager = target;
            targetName.text = target.info.name;
            bool result = hpBar.updateBar((float)target.info.currentHp / (float)target.info.maxHp);
            if (result) displayTimer = 0f;
        }

        private void setTargetToMonster(MonsterStateManager target) {
            this.targetStateManager = target;
            targetName.text = target.info.name;
            bool result = hpBar.updateBar((float)target.info.currentHp / (float)target.info.maxHp);
            if (result) displayTimer = 0f;
        }

        private void updateTarget() {
            var monsterTarget = playerStateManager.LastTarget as MonsterStateManager;
            if (monsterTarget != null) {
                this.setTargetToMonster(monsterTarget);
                return;
            }

            //var playerTarget = playerStateManager.LastTarget as PlayerStateManager;
            //if (playerTarget != null) {
            //    this.setTargetToPlayer(playerTarget);
            //    return;
            //}           
        }
    }
}