using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

namespace Heroes {
	public class ChanelManager : MonoBehaviour {
		private NetworkManager networkManager;
		private MessageBox msgBox;

		[SerializeField] private GameObject chanelInfoItem;
		
		private void Awake() {
			networkManager = GameObject.Find("Network Manager").GetComponent<NetworkManager>();
			msgBox = GameObject.Find("Message Handler").GetComponent<MessageBox>();

			networkManager.RegisterNotification(PacketType.ChanelStatusResponse, chanelStatusResponse);
		}

		private void Start() {
			this.chanelStatusRequest();
		}

		private void chanelStatusRequest() {
			ChanelStatusRequestPacket packet = new ChanelStatusRequestPacket();
			networkManager.send(packet);

			msgBox.notice("채널 정보를 불러오고 있습니다.");
		}

		public void chanelStatusResponse(PacketType type, Packet rowPacket) {
			msgBox.close();

			ChanelStatusResponsePacket packet = rowPacket as ChanelStatusResponsePacket;	
			if(packet == null) {
				Debug.Log("invalid packet");
				return;
			}
			
			GameObject list = GameObject.Find("List");			
			foreach(ChanelInfo info in packet.chanelList) {
				GameObject chanel = Instantiate(chanelInfoItem, list.transform);
				UIChanelInfo chanelInfo = chanel.GetComponent<UIChanelInfo>();
				chanelInfo.ID = info.id;
				chanelInfo.Traffic = info.traffic;
				chanelInfo.Name = info.name;
			}
		}
	}
}
