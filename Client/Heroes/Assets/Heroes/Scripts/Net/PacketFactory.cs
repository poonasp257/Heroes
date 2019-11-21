using System;

namespace Heroes {
	public static class PacketFactory {
		public static Packet CreatePacket(UInt32 type) {
			switch((PacketType)type) {
				case PacketType.ExitRequest: return new ExitRequestPacket();
				case PacketType.ExitResponse: return new ExitResponsePacket();
				case PacketType.AuthLoginRequest: return new AuthLoginRequestPacket();
				case PacketType.AuthLoginResponse: return new AuthLoginResponsePacket();
				case PacketType.AuthRegisterRequest: return new AuthRegisterRequestPacket();
				case PacketType.AuthRegisterResponse: return new AuthRegisterResponsePacket();
				case PacketType.ChanelStatusRequest: return new ChanelStatusRequestPacket();
				case PacketType.ChanelStatusResponse: return new ChanelStatusResponsePacket();
				case PacketType.AccountInfoRequest: return new AccountInfoRequestPacket();
				case PacketType.AccountInfoResponse: return new AccountInfoResponsePacket();
				case PacketType.CreateCharacterRequest: return new CreateCharacterRequestPacket();
				case PacketType.CreateCharacterResponse: return new CreateCharacterResponsePacket();
				case PacketType.DeleteCharacterRequest: return new DeleteCharacterRequestPacket();
				case PacketType.DeleteCharacterResponse: return new DeleteCharacterResponsePacket();
				case PacketType.ConnectChanelRequest: return new ConnectChanelRequestPacket();
				case PacketType.ConnectChanelResponse: return new ConnectChanelResponsePacket();
				case PacketType.DisconnectChanelRequest: return new DisconnectChanelRequestPacket();
				case PacketType.DisconnectChanelResponse: return new DisconnectChanelResponsePacket();
				case PacketType.CharacterMoveRequest: return new CharacterMoveRequestPacket();
				case PacketType.CharacterMoveResponse: return new CharacterMoveResponsePacket();
			}

			return null;
		}
	}
}