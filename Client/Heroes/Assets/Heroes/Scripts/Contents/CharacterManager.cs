using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public class AccountManager : MonoBehaviour {
		private NetworkManager networkManager;
		
		private void Start() {
			networkManager = GameObject.Find("NetworkManager").GetComponent<NetworkManager>();

			//networkManager.RegisterNotification(PacketType.ConnectChanelResponse);
			//networkManager.RegisterNotification(PacketType.CharacterMoveResponse);
 		}

		private void Update() {
			
		}

		//private void RequestConnectChanel() {
				

		//}

		//private void 
	}
}
