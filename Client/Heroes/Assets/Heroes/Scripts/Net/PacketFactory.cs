using System;

namespace Heroes {
	public static class PacketFactory {
		public static Packet CreatePacket(UInt32 type) {
			switch((PacketType)type) {
				case PacketType.AuthLoginRequest: return new AuthLoginRequestPacket();
				case PacketType.AuthLoginResponse: return new AuthLoginResponsePacket();
				case PacketType.AuthRegisterRequest: return new AuthRegisterRequestPacket();
				case PacketType.AuthRegisterResponse: return new AuthRegisterResponsePacket();
				case PacketType.ExitRequest: return new ExitRequestPacket();
				case PacketType.ExitResponse: return new ExitResponsePacket();
			}

			return null;
		}
	}
}