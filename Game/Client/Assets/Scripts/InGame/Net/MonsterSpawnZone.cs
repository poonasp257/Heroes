using System;
using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
    public class MonsterSpawnZone : MonoBehaviour {
        private struct MonsterScripts {
            public MonsterController controller;
            public MonsterStateManager stateManager;

            public MonsterScripts(MonsterController controller, MonsterStateManager stateManager) {
                this.controller = controller;
                this.stateManager = stateManager;
            }
        }

        private Dictionary<UInt64, MonsterScripts> monsterTable = new Dictionary<UInt64, MonsterScripts>();

        public UInt64 ZoneId { get; set; }

        public MonsterManager MonsterManager { get; set; }

        public MonsterStateManager getMonsterStateManager(UInt64 monsterId) {
            if (!monsterTable.ContainsKey(monsterId)) return null;

            return monsterTable[monsterId].stateManager;
        }

        public void createNewMonster(GameObject prefab, MonsterInfo info) {
            var newMonster = Instantiate(prefab, this.transform);
            newMonster.name = info.name;
            newMonster.tag = "Monster";
            newMonster.transform.position = info.position;
            newMonster.transform.localRotation = Quaternion.Euler(info.rotation);

            var stateManager = newMonster.AddComponent<MonsterStateManager>();
            stateManager.info = info;
            var controller = newMonster.AddComponent<MonsterController>();
            controller.stateManager = stateManager;
            controller.SpawnZone = this;
            controller.resetMovement();

            if(info.currentHp <= 0) {
                newMonster.SetActive(false);
            }

            monsterTable.Add(info.id, new MonsterScripts(controller, stateManager));
        }

        public void spawnMonster(UInt64 monsterId) {
            if (!monsterTable.ContainsKey(monsterId)) return;

            var stateManager = monsterTable[monsterId].stateManager;
            var controller = monsterTable[monsterId].controller;
            var monster = controller.gameObject;
            monster.SetActive(true);
            monster.transform.position = stateManager.info.originPosition;
            monster.transform.rotation = Quaternion.Euler(stateManager.info.originRotation);
            stateManager.info.currentHp = stateManager.info.maxHp;
            controller.resetMovement();
        }

        public void updateMonster(MonsterInfo monsterInfo) {
            if (!monsterTable.ContainsKey(monsterInfo.id)) return;

            var monsterScripts = monsterTable[monsterInfo.id];
            monsterScripts.stateManager.info = monsterInfo;
            monsterScripts.stateManager.transform.position = monsterInfo.position;
            if (monsterInfo.currentHp <= 0) {
                monsterScripts.stateManager.die();
            }
        }

        public void killMonster(UInt64 monsterId) {
            if (!monsterTable.ContainsKey(monsterId)) return;

            monsterTable[monsterId].stateManager.die();
        }

        public void loseAggressionMonster(UInt64 monsterId) {
            if (!monsterTable.ContainsKey(monsterId)) return;

            monsterTable[monsterId].controller.loseAggression();
        }

        public void takeDamage(UInt64 monsterId) {
            MonsterManager.takeDamageMonster(ZoneId, monsterId);
        }

        public void updateMovement(UInt64 monsterId, CharacterMovement movement) {
            if (!monsterTable.ContainsKey(monsterId)) return;

            monsterTable[monsterId].controller.updateMovement(movement);
        }
        public void executeAction(UInt64 monsterId, ActionType actionType) {
            if (!monsterTable.ContainsKey(monsterId)) return;

            monsterTable[monsterId].controller.stopMovement();
            monsterTable[monsterId].stateManager.executeAction(actionType);
        }        
    }
}