using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

namespace Heroes {
	public class ChannelManager : MonoBehaviour {
		private NetworkManager networkManager;
		private MessageBoxHandler messageBoxHandler;

		[SerializeField] private GameObject ChannelInfoItem;
		
		private void Start() {
			networkManager = GetComponent<NetworkManager>();
			messageBoxHandler = GameObject.Find("MessageBox Handler").GetComponent<MessageBoxHandler>();

			networkManager.RegisterNotification(PacketType.ChannelListResponse, ChannelListResponse);

			this.ChannelListRequest();
		}

		private void ChannelListRequest() {
			ChannelListRequestPacket packet = new ChannelListRequestPacket();
			networkManager.sendPacket(packet);

			messageBoxHandler.notice("채널 목록을 불러오고 있습니다.");
		}

		public void ChannelListResponse(PacketType type, Packet rowPacket) {
			messageBoxHandler.close();

			ChannelListResponsePacket packet = rowPacket as ChannelListResponsePacket;	
			if(packet == null) {
				Debug.Log("invalid packet");
				return;
			}
			
			GameObject list = GameObject.Find("List");			
			foreach(ChannelInfo info in packet.channelList) {
				GameObject Channel = Instantiate(ChannelInfoItem, list.transform);
				UIChannelInfo ChannelInfo = Channel.GetComponent<UIChannelInfo>();
				//ChannelInfo.ID = info.id;
				//ChannelInfo.Traffic = info.traffic;
				//ChannelInfo.Name = info.name;
			}
		}
	}
}
