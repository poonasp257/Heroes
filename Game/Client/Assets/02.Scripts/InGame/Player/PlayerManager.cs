using System;
using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public class PlayerManager : MonoBehaviour {
		private NetworkManager networkManager;

		private Dictionary<UInt64, CharacterStateManager> playerTable;
		private Queue<CharacterMovement> movementQueue;
		private Queue<ActionType> actionQueue;

		[SerializeField] private GameObject characterPrefab = null;

		private void Awake() {
			networkManager = GameObject.Find("Network Manager").GetComponent<NetworkManager>();

			playerTable = new Dictionary<ulong, CharacterStateManager>();
			movementQueue = new Queue<CharacterMovement>();
			actionQueue = new Queue<ActionType>();

			networkManager.RegisterNotification(PacketType.NotifyConnectPlayer, notifyConnectPlayer);
			networkManager.RegisterNotification(PacketType.NotifyDisconnectPlayer, notifyDisconnectPlayer);
			networkManager.RegisterNotification(PacketType.NotifyCharacterMovement, notifyCharacterMovement);
			networkManager.RegisterNotification(PacketType.NotifyCharacterAction, notifyCharacterAction);
		}
	
		private void Start() {
			DontDestroyOnLoad(this.gameObject);	
		}

		private void Update() {
			processCharacterMovement();
			processActionMovement();
		}

		private void processCharacterMovement() {
			if (movementQueue.Count == 0) return;
			
			NotifyCharacterMovementPacket packet = new NotifyCharacterMovementPacket();
			packet.accountId = PlayerData.Instance.AccountId;
			packet.movement = movementQueue.Dequeue();
			networkManager.sendPacket(packet);
		}

		private void processActionMovement() {
			if (actionQueue.Count == 0) return;
			
			NotifyCharacterActionPacket packet = new NotifyCharacterActionPacket();
			packet.accountId = PlayerData.Instance.AccountId;
			packet.actionType = actionQueue.Dequeue();
			networkManager.sendPacket(packet);
		}

		private GameObject createCharacter(UInt64 accountId, CharacterInfo info) {
			GameObject newCharacter = Instantiate<GameObject>(characterPrefab);
			newCharacter.transform.position = info.position;
			newCharacter.transform.rotation = Quaternion.Euler(info.rotation);
			
			var characterState = newCharacter.AddComponent<CharacterStateManager>();
			characterState.Info = info;
			DontDestroyOnLoad(newCharacter);

			playerTable.Add(accountId, characterState);

			return newCharacter;
		}

		public CharacterStateManager getCharacterState(UInt64 accountId) {
			if (!playerTable.ContainsKey(accountId)) return null;

			return playerTable[accountId];
		}
		
		public void activeAllPlayer() {
			foreach(var player in playerTable) {
				player.Value.gameObject.SetActive(true);
			}
		}

		public void inputMovement(CharacterMovement movement) {
			movementQueue.Enqueue(movement);
		}

		public void inputAction(ActionType action) {
			actionQueue.Enqueue(action);
		}

		public void notifyConnectPlayer(PacketType type, Packet rowPacket) {
			NotifyConnectPlayerPacket packet = rowPacket as NotifyConnectPlayerPacket;

			//if (playerTable.ContainsKey(packet.accountId)) return;

			//createCharacter(packet.accountId, packet.characterInfo);
		}

		public void notifyDisconnectPlayer(PacketType type, Packet rowPacket) {
			NotifyDisconnectPlayerPacket packet = rowPacket as NotifyDisconnectPlayerPacket;

			var character = playerTable[packet.accountId];
			Destroy(character.gameObject);

			playerTable.Remove(packet.accountId);
		}
		
		public void notifyCharacterMovement(PacketType type, Packet rowPacket) {
			NotifyCharacterMovementPacket packet = rowPacket as NotifyCharacterMovementPacket;

			if (packet.accountId == PlayerData.Instance.AccountId) return;

			playerTable[packet.accountId].UpdateTransform(packet.movement);
		}

		public void notifyCharacterAction(PacketType type, Packet rowPacket) {
			NotifyCharacterActionPacket packet = rowPacket as NotifyCharacterActionPacket;

			if (packet.accountId == PlayerData.Instance.AccountId) return;

			playerTable[packet.accountId].ExecuteAction(packet.actionType);
		}
	}
}