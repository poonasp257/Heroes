using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public class MonsterSpawner : MonoBehaviour {
		private NetworkManager monsterServer;

		private List<GameObject> monsterList;

		[SerializeField] private GameObject monsterPrefab;
		[SerializeField] private float spawnCycle = 10.0f;

		private void Awake() {
			//monsterServer = new NetworkManager();
			//monsterServer.connect("127.0.0.1", 9300);
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