using System;
using System.IO;

namespace Heroes {
	public abstract class Packet {
		protected MemoryStream stream = new MemoryStream();

		public MemoryStream getStream() { return stream; }
				
		public virtual void serialize() { Serializer.serialize(stream, type()); }
		public virtual void deserialize(Byte[] data, Int32 offset) { }
			   
		public abstract PacketType type();
	}

	public class AuthLoginRequestPacket : Packet {
		public string id;
		public string password;

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, id);
			Serializer.serialize(stream, password);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out id);
			Serializer.deserialize(data, ref offset, out password);
		}

		public override PacketType type() { return PacketType.AuthLoginRequest; }
	}

	public class AuthLoginResponsePacket : Packet {
		public bool success;

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, success);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out success);
		}

		public override PacketType type() { return PacketType.AuthLoginResponse; }
	}
	
	public class AuthRegisterRequestPacket : Packet {
		public string id;
		public string password;

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, id);
			Serializer.serialize(stream, password);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out id);
			Serializer.deserialize(data, ref offset, out password);
		}

		public override PacketType type() { return PacketType.AuthRegisterRequest; }
	}

	public class AuthRegisterResponsePacket : Packet {
		public override PacketType type() { return PacketType.AuthRegisterResponse; }
	}

	public class ExitRequestPacket : Packet {
		public override PacketType type() { return PacketType.ExitRequest; }
	}

	public class ExitResponsePacket : Packet {
		public override PacketType type() { return PacketType.ExitResponse; }
	}
}