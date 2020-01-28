using System;

namespace Heroes {
	public static class PacketFactory {
		public static Packet CreatePacket(UInt32 type) {
			switch((PacketType)type) {
				case PacketType.ExitRequest: return new ExitRequestPacket();
				case PacketType.ExitResponse: return new ExitResponsePacket();
				case PacketType.ChannelStatusRequest: return new ChannelStatusRequestPacket();
				case PacketType.ChannelStatusResponse: return new ChannelStatusResponsePacket();
				case PacketType.AccountInfoRequest: return new AccountInfoRequestPacket();
				case PacketType.AccountInfoResponse: return new AccountInfoResponsePacket();
				case PacketType.CreateCharacterRequest: return new CreateCharacterRequestPacket();
				case PacketType.CreateCharacterResponse: return new CreateCharacterResponsePacket();
				case PacketType.DeleteCharacterRequest: return new DeleteCharacterRequestPacket();
				case PacketType.DeleteCharacterResponse: return new DeleteCharacterResponsePacket();
				case PacketType.ConnectChannelRequest: return new ConnectChannelRequestPacket();
				case PacketType.ConnectChannelResponse: return new ConnectChannelResponsePacket();
				case PacketType.DisconnectChannelRequest: return new DisconnectChannelRequestPacket();
				case PacketType.DisconnectChannelResponse: return new DisconnectChannelResponsePacket();
				case PacketType.NotifyConnectPlayer: return new NotifyConnectPlayerPacket();
				case PacketType.NotifyDisconnectPlayer: return new NotifyDisconnectPlayerPacket();


				case PacketType.NotifyCharacterMovement: return new NotifyCharacterMovementPacket();
				case PacketType.NotifyCharacterAction: return new NotifyCharacterActionPacket();
			}

			return null;
		}
	}
}