using System;
using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
    public class MonsterManager : MonoBehaviour {
        private NetworkManager networkManager = null;

        private Dictionary<UInt64, MonsterSpawnZone> monsterZoneTable = new Dictionary<UInt64, MonsterSpawnZone>();
        [SerializeField] private GameObject[] monsterPrefabs;

        private void Awake() {
            ObjectManager.Instance.DontDestroyOnLoad(this.gameObject);
        }

        private void Start() {
            var connectedChannel = GameObject.Find("Channel Manager/Connected Channel");
            networkManager = connectedChannel?.GetComponent<NetworkManager>();
            if (networkManager == null) throw new Exception("Connected channel not found");

            networkManager.registerNotification(PacketType.GetMonsterList, getMonsterList);
            networkManager.registerNotification(PacketType.NotifyMonsterMovement, notifyMonsterMovement);
            networkManager.registerNotification(PacketType.NotifyMonsterAction, notifyMonsterAction);
            networkManager.registerNotification(PacketType.NotifyTakeDamageMonster, notifyTakeDamageMonster);
            networkManager.registerNotification(PacketType.NotifyRespawnMonster, notifyRespawnMonster);
            networkManager.registerNotification(PacketType.NotifyLoseAggressionMonster, notifyLoseAggressionMonster);

            this.gameObject.SetActive(false);
        }

        private void OnDestroy() {
            networkManager.unregisterNotification(PacketType.GetMonsterList);
            networkManager.unregisterNotification(PacketType.NotifyMonsterMovement);
            networkManager.unregisterNotification(PacketType.NotifyMonsterAction);
            networkManager.unregisterNotification(PacketType.NotifyTakeDamageMonster);
            networkManager.unregisterNotification(PacketType.NotifyRespawnMonster);
        }

        private void getMonsterList(Packet rowPacket) {
            var packet = rowPacket as GetMonsterListPacket;
            var zoneInfo = packet.monsterZone;
            if(!monsterZoneTable.ContainsKey(zoneInfo.id)) {
                var newZone = new GameObject();
                newZone.name = string.Format("Monster Zone-{0}", zoneInfo.id);
                newZone.transform.parent = this.transform;
                newZone.transform.position = zoneInfo.position;
                
                var monsterZoneScript = newZone.AddComponent<MonsterSpawnZone>();
                monsterZoneScript.MonsterManager = this;
                monsterZoneScript.ZoneId = zoneInfo.id;
                foreach (var monsterInfo in zoneInfo.monsterList) {
                    monsterZoneScript.createNewMonster(monsterPrefabs[monsterInfo.typeId], monsterInfo);
                }

                monsterZoneTable.Add(zoneInfo.id, monsterZoneScript);
            }

            var monsterZone = monsterZoneTable[zoneInfo.id];
            foreach (var monsterInfo in zoneInfo.monsterList) {
                monsterZone.updateMonster(monsterInfo);
            }
        }

        private void notifyMonsterMovement(Packet rowPacket) {
            if (!this.gameObject.activeSelf) return;
            
            var packet = rowPacket as NotifyMonsterMovementPacket;
            if (!monsterZoneTable.ContainsKey(packet.zoneId)) return;

            var monsterZone = monsterZoneTable[packet.zoneId];
            monsterZone.updateMovement(packet.monsterId, packet.movement);
        }

        private void notifyMonsterAction(Packet rowPacket) {
            if (!this.gameObject.activeSelf) return;

            var packet = rowPacket as NotifyMonsterActionPacket;
            if (!monsterZoneTable.ContainsKey(packet.zoneId)) return;

            var monsterZone = monsterZoneTable[packet.zoneId];
            monsterZone.executeAction(packet.monsterId, packet.actionType);
        }

        private void notifyTakeDamageMonster(Packet rowPacket) {
            if (!this.gameObject.activeSelf) return;

            var packet = rowPacket as NotifyTakeDamageMonsterPacket;
            if (!monsterZoneTable.ContainsKey(packet.zoneId)) return;

            var stateManager = monsterZoneTable[packet.zoneId].getMonsterStateManager(packet.monsterId);
            stateManager.info.currentHp = packet.hp;
            if (stateManager.info.currentHp <= 0) {
                monsterZoneTable[packet.zoneId].killMonster(packet.monsterId);
                return;
            }

            stateManager.executeAction(ActionType.Hit);
        }

        private void notifyRespawnMonster(Packet rowPacket) {
            var packet = rowPacket as NotifyRespawnMonsterPacket;
            if (!monsterZoneTable.ContainsKey(packet.zoneId)) return;

            monsterZoneTable[packet.zoneId].spawnMonster(packet.monsterId);
        }

        private void notifyLoseAggressionMonster(Packet rowPacket) {
            var packet = rowPacket as NotifyLoseAggressionMonsterPacket;
            if (!monsterZoneTable.ContainsKey(packet.zoneId)) return;

            monsterZoneTable[packet.zoneId].loseAggressionMonster(packet.monsterId);
        }

        public void takeDamageMonster(UInt64 zoneId, UInt64 monsterId) {
            var packet = new TakeDamageMonsterPacket();
            packet.accessKey = AccountData.Instance.accessKey;
            packet.zoneId = zoneId;
            packet.monsterId = monsterId;
            packet.playerId = AccountData.Instance.PlayerId;
            networkManager.sendPacket(packet);
        }
        
        public void executeAction(UInt64 zoneId, UInt64 monsterId, ActionType type) {
            if (!monsterZoneTable.ContainsKey(zoneId)) return;

            monsterZoneTable[zoneId].executeAction(monsterId, type);
        }
    }
}