using System;
using UnityEngine;

namespace Heroes {
	public class LobbyManager : MonoBehaviour {
		private NetworkManager networkManager;
		private MessageBox msgBox;

		//private UInt64 accountId;
		//private string accountId;

		public string AccountId { get; set; }
		
		private void Start() {
			networkManager = GameObject.Find("NetworkManager").GetComponent<NetworkManager>();
			msgBox = GameObject.Find("MessageHandler").GetComponent<MessageBox>();

			ChanelStatusRequestPacket packet = new ChanelStatusRequestPacket();
			networkManager.send(packet);

			networkManager.RegisterNotification(PacketType.ChanelStatusResponse, ChanelStatusResponse);
		}
		
		private void Update() {
			
		}

		public void ChanelStatusResponse(PacketType type, Packet rowPacket) {
			ChanelStatusResponsePacket packet = rowPacket as ChanelStatusResponsePacket;	
			if(packet == null) {
				Debug.Log("invalid packet");
				return;
			}

			msgBox.close();
			
			foreach(ChanelStatus status in packet.chanelList) {
				Debug.Log(status.traffic);
				Debug.Log(status.id);
			}
		}
	}
}
