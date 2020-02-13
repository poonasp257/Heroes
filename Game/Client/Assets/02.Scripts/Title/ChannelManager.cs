using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public class ChannelManager : MonoBehaviour {
		public delegate void CreateChannelListAction(List<ChannelInfo> channelList);

		private NetworkManager networkManager;
		private MessageBoxHandler messageBoxHandler;
		private CreateChannelListAction createChannelListAction;

		private void Start() {
			networkManager = GetComponent<NetworkManager>();
			networkManager.RegisterNotification(PacketType.GetChannelListResponse, getChannelListResponse);

			var msgBoxHandlerObj = GameObject.Find("MessageBox Handler");
			messageBoxHandler = msgBoxHandlerObj?.GetComponent<MessageBoxHandler>();

			DontDestroyOnLoad(this.gameObject);
		}

		private void OnDestroy() {
			networkManager.UnregisterNotification(PacketType.GetChannelListResponse);
		}

		private void getChannelListResponse(PacketType type, Packet rowPacket) {
            messageBoxHandler.close();

			GetChannelListResponsePacket packet = rowPacket as GetChannelListResponsePacket;
			createChannelListAction?.Invoke(packet.channelList);
		}

		public void getChannelListRequest(CreateChannelListAction action) {
			createChannelListAction = action;

			GetChannelListRequestPacket packet = new GetChannelListRequestPacket();
			networkManager.sendPacket(packet);
			messageBoxHandler.notice("채널 목록을 불러오고 있습니다.");
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