using System;

namespace Heroes {
	public static class PacketFactory {
		public static Packet CreatePacket(UInt32 type) {
			switch((PacketType)type) {
				case PacketType.ExitRequest: return new ExitRequestPacket();
				case PacketType.ExitResponse: return new ExitResponsePacket();
				case PacketType.GetChannelListRequest: return new GetChannelListRequestPacket();
				case PacketType.GetChannelListResponse: return new GetChannelListResponsePacket();
				case PacketType.SearchAccountRequest: return new SearchAccountRequestPacket();
				case PacketType.SearchAccountResponse: return new SearchAccountResponsePacket();
				case PacketType.CreateAccountRequest: return new CreateAccountRequestPacket();
				case PacketType.CreateAccountResponse: return new CreateAccountResponsePacket();
				case PacketType.GetCharacterListRequest: return new GetCharacterListRequestPacket();
				case PacketType.GetCharacterListResponse: return new GetCharacterListResponsePacket();
				case PacketType.ChangeCharacterOrderRequest: return new ChangeCharacterOrderRequestPacket();
				case PacketType.ChangeCharacterOrderResponse: return new ChangeCharacterOrderResponsePacket();
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