using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public class MonsterSpawner : MonoBehaviour {
		private NetworkManager networkManager;

		private List<GameObject> monsterList;

		[SerializeField] private GameObject monsterPrefab;
		[SerializeField] private float spawnCycle = 10.0f;

		private void Start() {
			GameObject networkObject = GameObject.Find("Network Manager");
			if (!networkObject) {
				Debug.Log("Network Manager doens't exist");
				return;
			}
			
			networkManager = networkObject.GetComponent<NetworkManager>();
			//networkManager.RegisterNotification(PacketType.NotifyCharacterAction, notifyCharacterAction);
		}

		private void Update() { 
			
		}

		private void Spawn() {

		}

		private void monsterSpawnReqeust() {
			
		}

		private void monsterSpawnResponse(PacketType type, Packet rowPacket) {
				

		}
	}
}