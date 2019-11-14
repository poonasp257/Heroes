using System;

namespace Heroes {
	public static class PacketUtil {
		public static Int32 GetHeader(Byte[] packetData, ref Int32 offset) {
			Int32 header = BitConverter.ToInt32(packetData, offset);
			offset += sizeof(Int32);

			return header;
		}

		public static Packet AnalyzerPacket(Byte[] packetData) {
			Int32 offset = 0;
			UInt32 packetType = BitConverter.ToUInt32(packetData, offset);
			offset += sizeof(UInt32);

			Packet packet = PacketFactory.CreatePacket(packetType);
			if (packet == null) return null;

			if (offset < packetData.Length) {
				packet.deserialize(packetData, offset);
			}

			return packet;
		}
	}
}