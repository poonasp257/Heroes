using System;
using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public class PlayerManager : MonoBehaviour {
		private NetworkManager networkManager = null;

		private List<KeyValuePair<UInt64, CharacterStateManager>> playerList = null;
		private Queue<CharacterMovement> movementQueue = null;
		private Queue<ActionType> actionQueue = null;

		[SerializeField] private GameObject characterPrefab = null;

		private void Awake() {
			playerList = new List<KeyValuePair<UInt64, CharacterStateManager>>();
			movementQueue = new Queue<CharacterMovement>();
			actionQueue = new Queue<ActionType>();
		}
	
		private void Start() {
			var connectedChannel = GameObject.Find("Channel Manager/Connected Channel");
			networkManager = connectedChannel?.GetComponent<NetworkManager>();
			if (networkManager == null) throw new Exception("Connected channel not found");

			networkManager.RegisterNotification(PacketType.NotifyConnectPlayer, notifyConnectPlayer);
			networkManager.RegisterNotification(PacketType.NotifyDisconnectPlayer, notifyDisconnectPlayer);
			networkManager.RegisterNotification(PacketType.NotifyCharacterMovement, notifyCharacterMovement);
			networkManager.RegisterNotification(PacketType.NotifyCharacterAction, notifyCharacterAction);

			Debug.Log(AccountData.Instance.FamilyName);
		}

		private void OnDestroy() {
			networkManager.UnregisterNotification(PacketType.NotifyConnectPlayer);
			networkManager.UnregisterNotification(PacketType.NotifyDisconnectPlayer);
			networkManager.UnregisterNotification(PacketType.NotifyCharacterMovement);
			networkManager.UnregisterNotification(PacketType.NotifyCharacterAction);
		}

		private void Update() {
			processCharacterMovement();
			processActionMovement();
		}

		private void processCharacterMovement() {
			if (movementQueue.Count == 0) return;
			
			NotifyCharacterMovementPacket packet = new NotifyCharacterMovementPacket();
			packet.accessKey = AccountData.Instance.accessKey;
			packet.movement = movementQueue.Dequeue();
			networkManager.sendPacket(packet);
		}

		private void processActionMovement() {
			if (actionQueue.Count == 0) return;
			
			NotifyCharacterActionPacket packet = new NotifyCharacterActionPacket();
			packet.accessKey = AccountData.Instance.accessKey;
			packet.actionType = actionQueue.Dequeue();
			networkManager.sendPacket(packet);
		}

		private CharacterStateManager createCharacter(UInt64 playerId, PlayerInfo info) {
			GameObject newCharacter = Instantiate(characterPrefab);
			newCharacter.transform.position = info.characterInfo.position;
			newCharacter.transform.rotation = Quaternion.Euler(info.characterInfo.rotation);
			newCharacter.name = info.familyName;
			newCharacter.tag = "Player";

			var characterState = newCharacter.AddComponent<CharacterStateManager>();
			characterState.Info = info.characterInfo;
			DontDestroyOnLoad(newCharacter);

			return characterState;
		}

		public void initialize(List<KeyValuePair<UInt64, PlayerInfo>> players) {
			foreach (var player in players) {
				var character = this.createCharacter(player.Key, player.Value);
				playerList.Add(new KeyValuePair<UInt64, CharacterStateManager>(player.Key, character));
			}
		}

		public CharacterStateManager getCharacterState(string accessKey) {
			//if(playerList.Contains())

			//if (!playerTable.ContainsKey(accessKey)) 
					return null;

			//return playerTable[accessKey];
		}
		
		public void activeAllPlayer() {
			foreach(var player in playerList) {
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

			//if (playerTable.ContainsKey(packet.accessKey)) return;

			//createCharacter(packet.accessKey, packet.characterInfo);
		}

		public void notifyDisconnectPlayer(PacketType type, Packet rowPacket) {
			//NotifyDisconnectPlayerPacket packet = rowPacket as NotifyDisconnectPlayerPacket;

			//var character = playerTable[packet.playerId];
			//Destroy(character.gameObject);

			//playerTable.Remove(packet.accessKey);
		}
		
		public void notifyCharacterMovement(PacketType type, Packet rowPacket) {
			//NotifyCharacterMovementPacket packet = rowPacket as NotifyCharacterMovementPacket;

			//if (packet.accessKey == AccountData.Instance.accessKey) return;

			//playerTable[packet.accessKey].UpdateTransform(packet.movement);
		}

		public void notifyCharacterAction(PacketType type, Packet rowPacket) {
			//NotifyCharacterActionPacket packet = rowPacket as NotifyCharacterActionPacket;

			//if (packet.accessKey == AccountData.Instance.accessKey) return;

			//playerList[packet.accessKey].ExecuteAction(packet.actionType);
		}
	}
}