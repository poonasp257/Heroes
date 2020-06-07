using System;
using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public class ChannelManager : MonoBehaviour {
		private NetworkManager networkManager;
		private MessageBoxHandler messageBoxHandler;

		private UIChannelList channelListUI;

		private void Awake() {
			ObjectManager.Instance.DontDestroyOnLoad(this.gameObject);
		}

		private void Start() {
			var msgBoxHandlerObj = GameObject.Find("MessageBox Handler");
			messageBoxHandler = msgBoxHandlerObj?.GetComponent<MessageBoxHandler>();
			if (messageBoxHandler == null) throw new Exception("MessageBox Handler not found");

			var channelListUIObj = GameObject.Find("Channel List");
			channelListUI = channelListUIObj?.GetComponent<UIChannelList>();
			if (channelListUI == null) throw new Exception("Channel List UI not found");

			networkManager = GetComponent<NetworkManager>();
			networkManager.connectServer();
			networkManager.registerNotification(PacketType.GetChannelListResponse, getChannelListResponse);
			
			this.getChannelListRequest();
		}

		private void OnDestroy() {
			networkManager.unregisterNotification(PacketType.GetChannelListResponse);
		}

		private void getChannelListRequest() {
			var packet = new GetChannelListRequestPacket();
			networkManager.sendPacket(packet);
			messageBoxHandler.notice("채널 목록을 불러오고 있습니다.");
		}

		private void getChannelListResponse(Packet rowPacket) {
            messageBoxHandler.close();

			var packet = rowPacket as GetChannelListResponsePacket;
			channelListUI.createChannelBoxes(packet.channelList);
		}

		public void connectToChannel(string ip, int port) {
			var channel = transform.Find("Connected Channel")?.gameObject;
			if(channel == null) {
				channel = new GameObject("Connected Channel");
				channel.transform.parent = this.transform;
			}

			var channelNetManager = channel.GetComponent<NetworkManager>();
			if (channelNetManager == null) { 
				channelNetManager = channel.AddComponent<NetworkManager>();
			}

			channelNetManager.connect(ip, port);
		}
	}
}