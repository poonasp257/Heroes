using System;
using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public class PlayerManager : MonoBehaviour {
		public struct PlayerScripts {
			public BaseController controller;
			public PlayerStateManager stateManager;

			public PlayerScripts(BaseController controller, PlayerStateManager stateManager) {
				this.controller = controller;
				this.stateManager = stateManager;
			} 
		}

		private NetworkManager networkManager = null;
		private MessageBoxHandler messageBoxHandler = null;
		[SerializeField] private MonsterManager monsterManager = null;
		private LinkedList<KeyValuePair<UInt64, PlayerScripts>> playerList = new LinkedList<KeyValuePair<UInt64, PlayerScripts>>();

		[Header("Character Prefabs")]
		[SerializeField] private GameObject[] characterPrefabs = null;
		[SerializeField] private GameObject levelUpParticle = null;

		private void Awake() {
			ObjectManager.Instance.DontDestroyOnLoad(this.gameObject);
		}

		private void Start() {
			var connectedChannel = GameObject.Find("Channel Manager/Connected Channel");
			networkManager = connectedChannel?.GetComponent<NetworkManager>();
			if (networkManager == null) throw new Exception("Connected channel not found");

			var msgBoxHandlerObj = GameObject.Find("MessageBox Handler");
			messageBoxHandler = msgBoxHandlerObj?.GetComponent<MessageBoxHandler>();
			if (messageBoxHandler == null) throw new Exception("MessageBox Handler not found");

			networkManager.registerNotification(PacketType.GainMonsterExp, gainMonsterExp);
			networkManager.registerNotification(PacketType.NotifyLevelUpPlayer, notifyLevelUpPlayer);
			networkManager.registerNotification(PacketType.NotifyTakeDamagePlayer, notifyTakeDamagePlayer);
			networkManager.registerNotification(PacketType.NotifyPlayerRevive, notifyPlayerRevive);
			networkManager.registerNotification(PacketType.NotifyPlayerDead, notifyPlayerDead);
			networkManager.registerNotification(PacketType.NotifyConnectPlayer, notifyConnectPlayer);
			networkManager.registerNotification(PacketType.NotifyDisconnectPlayer, notifyDisconnectPlayer);
			networkManager.registerNotification(PacketType.NotifyPlayerMovement, notifyPlayerMovement);
			networkManager.registerNotification(PacketType.NotifyPlayerAction, notifyPlayerAction);
			networkManager.registerNotification(PacketType.RevivePlayerResponse, revivePlayerResponse);

			this.gameObject.SetActive(false);
		}

		private void OnDestroy() {
			networkManager.unregisterNotification(PacketType.GainMonsterExp);
			networkManager.unregisterNotification(PacketType.NotifyLevelUpPlayer);
			networkManager.unregisterNotification(PacketType.NotifyTakeDamagePlayer);
			networkManager.unregisterNotification(PacketType.NotifyPlayerRevive);
			networkManager.unregisterNotification(PacketType.NotifyPlayerDead);
			networkManager.unregisterNotification(PacketType.NotifyConnectPlayer);
			networkManager.unregisterNotification(PacketType.NotifyDisconnectPlayer);
			networkManager.unregisterNotification(PacketType.NotifyPlayerMovement);
			networkManager.unregisterNotification(PacketType.NotifyPlayerAction);
			networkManager.unregisterNotification(PacketType.RevivePlayerResponse);
		}

		private void gainMonsterExp(Packet rowPacket) {
			var packet = rowPacket as GainMonsterExpPacket;
			var stateManager = this.getPlayerState(packet.playerId);
			stateManager.info.exp = packet.exp;
		}

		private void notifyLevelUpPlayer(Packet rowPacket) {
			var packet = rowPacket as NotifyLevelUpPlayerPacket;
			var stateManager = this.getPlayerState(packet.playerId);
			stateManager.info = packet.characterInfo;

			var particle = Instantiate(levelUpParticle, stateManager.gameObject.transform);
			Destroy(particle, 5.0f);
		}

		private void notifyTakeDamagePlayer(Packet rowPacket) {
			if (!this.gameObject.activeSelf) return;

			var packet = rowPacket as NotifyTakeDamagePlayerPacket;
			monsterManager.executeAction(packet.zoneId, packet.monsterId, packet.monsterActionType);

			var stateManager = this.getPlayerState(packet.playerId);
			if (stateManager == null) return;

			stateManager.executeAction(ActionType.Hit);
			stateManager.info.currentHp = packet.playerHp;
		}
		
		private void notifyPlayerDead(Packet rowPacket) {
			if (!this.gameObject.activeSelf) return;

			var packet = rowPacket as NotifyPlayerDeadPacket;
			var stateManager = this.getPlayerState(packet.playerId);
			if (stateManager == null) return;

			stateManager.die();
		}

		private void notifyPlayerRevive(Packet rowPacket) {
			if (!this.gameObject.activeSelf) return;

			var packet = rowPacket as NotifyPlayerRevivePacket;
			var stateManager = this.getPlayerState(packet.playerId);
			stateManager.executeAction(ActionType.Revive);
		}

		private void notifyConnectPlayer(Packet rowPacket) {
			var packet = rowPacket as NotifyConnectPlayerPacket;
			var stateManager = this.createPlayerStateManager("Other Player", 
				packet.playerInfo.familyName, packet.playerInfo.characterInfo);
			var controller = stateManager.gameObject.AddComponent<BaseController>();
			var scripts = new PlayerScripts(controller, stateManager);
			if(stateManager.info.currentHp <= 0) stateManager.die();

			playerList.AddLast(new KeyValuePair<UInt64, PlayerScripts>(packet.playerInfo.id, scripts));
		}

		private void notifyDisconnectPlayer(Packet rowPacket) {
			var packet = rowPacket as NotifyDisconnectPlayerPacket;
			var node = playerList.First;
			while (node != null) {
				var nextNode = node.Next;
				if (node.Value.Key == packet.playerId) {
					PlayerScripts scripts = node.Value.Value;
					Destroy(scripts.controller.gameObject);
					playerList.Remove(node);
					return;
				}

				node = nextNode;
			}
		}

		private void notifyPlayerMovement(Packet rowPacket) {
			if (!this.gameObject.activeSelf) return;

			var packet = rowPacket as NotifyPlayerMovementPacket;
			foreach (var player in playerList) {
				if (player.Key != packet.playerId) continue;

				player.Value.controller.updateMovement(packet.movement);
				break;
			}
		}

		private void notifyPlayerAction(Packet rowPacket) {
			if (!this.gameObject.activeSelf) return;
			
			var packet = rowPacket as NotifyPlayerActionPacket;
			foreach (var player in playerList) {
				if (player.Key != packet.playerId) continue;

				player.Value.stateManager.executeAction(packet.actionType);
				player.Value.controller.updateMovement(packet.movement);
				player.Value.controller.stopMovement();
				break;
			}
		}

		private GameObject createPrefab(CharacterClassType characterClass) {
			switch(characterClass) {
				case CharacterClassType.Warrior:
					return Instantiate(characterPrefabs[0], this.transform);
				case CharacterClassType.Crusader:
					return Instantiate(characterPrefabs[1], this.transform);
				case CharacterClassType.Archer:
					return Instantiate(characterPrefabs[2], this.transform);
				case CharacterClassType.Assassin:
					return Instantiate(characterPrefabs[3], this.transform);
				case CharacterClassType.Wizard:
					return Instantiate(characterPrefabs[4], this.transform);
				case CharacterClassType.Elementalist:
					return Instantiate(characterPrefabs[5], this.transform);
				default:
					return null;
			}
		}

		private PlayerStateManager createPlayerStateManager(string tag, string familyName, CharacterInfo info) {
			GameObject newCharacter = this.createPrefab(info.type);
			newCharacter.transform.position = info.position;
			newCharacter.transform.rotation = Quaternion.Euler(info.rotation);
			newCharacter.name = info.name;
			newCharacter.tag = tag;

			newCharacter.AddComponent<WeaponController>();
			var characterState = newCharacter.AddComponent<PlayerStateManager>();
			characterState.FamilyName = familyName;
			characterState.info = info;
			return characterState;
		}

		public void generatePlayerCharacter(UInt64 playerId) {
			var playerStateManager = this.createPlayerStateManager("Player",
				AccountData.Instance.FamilyName,
				AccountData.Instance.CurrentCharacter);
			var playerController = playerStateManager.gameObject.AddComponent<PlayerController>();
			PlayerScripts playerScripts = new PlayerScripts(playerController, playerStateManager);
			playerList.AddLast(new KeyValuePair<UInt64, PlayerScripts>(playerId, playerScripts));
		}

		public BaseController getPlayerController(UInt64 playerId) {
			foreach (var player in playerList) {
				if (player.Key != playerId) continue;

				return player.Value.controller;
			}

			return null;
		}

		public PlayerStateManager getPlayerState(UInt64 playerId) {
			foreach (var player in playerList) {
				if (player.Key != playerId) continue;

				return player.Value.stateManager;
			}

			return null;
		}

		public void notifyMovement(CharacterMovement movement) {
			var packet = new NotifyPlayerMovementPacket();
			packet.playerId = AccountData.Instance.PlayerId;
			packet.movement = movement;
			networkManager.sendPacket(packet);
		}

		public void notifyAction(ActionType actionType, CharacterMovement movement) {
			var packet = new NotifyPlayerActionPacket();
			packet.playerId = AccountData.Instance.PlayerId;
			packet.actionType = actionType;
			packet.movement = movement;
			networkManager.sendPacket(packet);
		}

		public void activeRequestReviveWindow() {
			if (messageBoxHandler.IsOpened) return;

            messageBoxHandler.confirm("부활하시겠습니까?", () => {
                var packet = new RevivePlayerRequestPacket();
                packet.playerId = AccountData.Instance.PlayerId;
                networkManager.sendPacket(packet);

				messageBoxHandler.notice("요청하고 있습니다.");
			});
        }

		private void revivePlayerResponse(Packet rowPacket) {
			messageBoxHandler.close();

			var stateManager = this.getPlayerState(AccountData.Instance.PlayerId);
			stateManager.info.currentHp = stateManager.info.maxHp;
			stateManager.executeAction(ActionType.Revive);
		}
	}
}