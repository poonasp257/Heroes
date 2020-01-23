using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

namespace Heroes {
	public class ChannelManager : MonoBehaviour {
		private NetworkManager networkManager;
		private MessageBox msgBox;

		[SerializeField] private GameObject ChannelInfoItem;
		
		private void Awake() {
			networkManager = GameObject.Find("Network Manager").GetComponent<NetworkManager>();
			msgBox = GameObject.Find("Message Handler").GetComponent<MessageBox>();

			networkManager.RegisterNotification(PacketType.ChannelStatusResponse, ChannelStatusResponse);
		}

		private void Start() {
			this.ChannelStatusRequest();
		}

		private void ChannelStatusRequest() {
			ChannelStatusRequestPacket packet = new ChannelStatusRequestPacket();
			networkManager.send(packet);

			msgBox.notice("채널 정보를 불러오고 있습니다.");
		}

		public void ChannelStatusResponse(PacketType type, Packet rowPacket) {
			msgBox.close();

			ChannelStatusResponsePacket packet = rowPacket as ChannelStatusResponsePacket;	
			if(packet == null) {
				Debug.Log("invalid packet");
				return;
			}
			
			GameObject list = GameObject.Find("List");			
			foreach(ChannelInfo info in packet.ChannelList) {
				GameObject Channel = Instantiate(ChannelInfoItem, list.transform);
				UIChannelInfo ChannelInfo = Channel.GetComponent<UIChannelInfo>();
				ChannelInfo.ID = info.id;
				ChannelInfo.Traffic = info.traffic;
				ChannelInfo.Name = info.name;
			}
		}
	}
}
