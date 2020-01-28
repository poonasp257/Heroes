using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public class MonsterSpawnerManager : MonoBehaviour {
		private NetworkManager monsterServer;
		
		private void Awake() {
			monsterServer = new NetworkManager();
			monsterServer.connect("127.0.0.1", 9300);
		}

		private void Update() {
			
		}
	}
}