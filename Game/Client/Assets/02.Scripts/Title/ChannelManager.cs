using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public class ChannelManager : MonoBehaviour {
		public delegate void CreateChannelListAction(List<ChannelInfo> channelList);

		private NetworkManager networkManager;
		private CreateChannelListAction createChannelListAction;

		private void Start() {
			networkManager = GetComponent<NetworkManager>();
			networkManager.RegisterNotification(PacketType.ChannelListResponse, channelListResponse);

			DontDestroyOnLoad(this.gameObject);
		}

		private void channelListResponse(PacketType type, Packet rowPacket) {
			ChannelListResponsePacket packet = rowPacket as ChannelListResponsePacket;
			createChannelListAction?.Invoke(packet.channelList);
		}

		public void channelListRequest(CreateChannelListAction action) {
			ChannelListRequestPacket packet = new ChannelListRequestPacket();
			networkManager.sendPacket(packet);

			createChannelListAction = action;
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
