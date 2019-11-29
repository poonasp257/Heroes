using System;
using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public class PlayerManager : MonoBehaviour {
		private NetworkManager networkManager;

		private Dictionary<UInt64, CharacterStateManager> playerTable;
		private Queue<CharacterMovement> movementQueue;
		private Queue<CharacterAction> actionQueue;

		[SerializeField] private GameObject characterPrefab;

		private void Awake() {
			networkManager = GameObject.Find("Network Manager").GetComponent<NetworkManager>();

			playerTable = new Dictionary<ulong, CharacterStateManager>();
			movementQueue = new Queue<CharacterMovement>();
			actionQueue = new Queue<CharacterAction>();

			networkManager.RegisterNotification(PacketType.ConnectChanelResponse, connectChanelResponse);
			networkManager.RegisterNotification(PacketType.NotifyNewConnect, notifyNewConnect);
			networkManager.RegisterNotification(PacketType.NotifyCharacterMovement, notifyCharacterMovement);
			networkManager.RegisterNotification(PacketType.NotifyCharacterAction, notifyCharacterAction);
		}
	
		private void Start() {
			DontDestroyOnLoad(this.gameObject);	

			this.connectChanelRequest();
		}

		private void Update() {
			ProcessCharacterMovement();
			ProcessActionMovement();
		}

		private void ProcessCharacterMovement() {
			if (movementQueue.Count == 0) return;
			
			var movement = movementQueue.Dequeue();
			NotifyCharacterMovementPacket packet = new NotifyCharacterMovementPacket();
			packet.accountId = PlayerData.Instance.AccountId;
			packet.movement = movement;

			networkManager.send(packet);
		}

		private void ProcessActionMovement() {
			if (actionQueue.Count == 0) return;
			
			var action = actionQueue.Dequeue();
			NotifyCharacterActionPacket packet = new NotifyCharacterActionPacket();
			packet.accountId = PlayerData.Instance.AccountId;
			packet.actionType = action.type;

			networkManager.send(packet);
		}

		private GameObject CreateCharacter(UInt64 accountId, CharacterInfo info) {
			GameObject newCharacter = Instantiate<GameObject>(characterPrefab);
			newCharacter.transform.position = info.position;
			newCharacter.transform.rotation = Quaternion.Euler(info.rotation);
			
			var characterState = newCharacter.AddComponent<CharacterStateManager>();
			characterState.Info = info;
			DontDestroyOnLoad(newCharacter);

			playerTable.Add(accountId, characterState);

			return newCharacter;
		}

		public void ActiveAllPlayer() {
			foreach(var player in playerTable) {
				player.Value.gameObject.SetActive(true);
			}
		}

		public void inputMovement(CharacterMovement movement) {
			movementQueue.Enqueue(movement);
		}

		public void inputAction(CharacterAction action) {
			actionQueue.Enqueue(action);
		}
				
		public void connectChanelRequest() {
			ConnectChanelRequestPacket packet = new ConnectChanelRequestPacket();
			packet.chanelId = PlayerData.Instance.ChanelId;
			packet.accountId = PlayerData.Instance.AccountId;
			packet.characterId = PlayerData.Instance.CharacterId;

			networkManager.send(packet);
		}

		public void connectChanelResponse(PacketType type, Packet rowPacket) {
			ConnectChanelResponsePacket packet = rowPacket as ConnectChanelResponsePacket;

			foreach(var info in packet.playerTable) {
				var playerInfo = info.Value;

				GameObject player = CreateCharacter(info.Key, playerInfo);
				player.SetActive(false);

				if (info.Key == PlayerData.Instance.AccountId) { 
					player.tag = "Player";
					player.AddComponent<PlayerController>();
				}
			}
		}

		public void notifyNewConnect(PacketType type, Packet rowPacket) {
			NotifyNewConnectPacket packet = rowPacket as NotifyNewConnectPacket;

			if (playerTable.ContainsKey(packet.accountId)) return;

			CreateCharacter(packet.accountId, packet.characterInfo);
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