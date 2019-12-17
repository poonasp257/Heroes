using System;
using System.IO;
using System.Collections.Generic;
using UnityEngine;

namespace Heroes {
	public abstract class Packet {
		protected MemoryStream stream = new MemoryStream();

		public MemoryStream getStream() { return stream; }
				
		public virtual void serialize() { Serializer.serialize(stream, type()); }
		public virtual void deserialize(Byte[] data, Int32 offset) { }
			   
		public abstract PacketType type();
	}

	public class ExitRequestPacket : Packet {
		public override PacketType type() { return PacketType.ExitRequest; }
	}

	public class ExitResponsePacket : Packet {
		public override PacketType type() { return PacketType.ExitResponse; }
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
		public Int16 errorCode;
		public UInt64 accountId;

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, errorCode);
			Serializer.serialize(stream, accountId);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out errorCode);
			Serializer.deserialize(data, ref offset, out accountId);
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
		public Int16 errorCode;

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, errorCode);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out errorCode);
		}

		public override PacketType type() { return PacketType.AuthRegisterResponse; }
	}

	public class ChanelStatusRequestPacket : Packet {
		public override PacketType type() { return PacketType.ChanelStatusRequest; }
	}

	public class ChanelStatusResponsePacket : Packet {
		public List<ChanelInfo> chanelList = new List<ChanelInfo>();

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, chanelList);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, ref chanelList);
		}
		
		public override PacketType type() { return PacketType.ChanelStatusResponse; }
	}

	public class AccountInfoRequestPacket : Packet {
		public UInt64 accountId;

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, accountId);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out accountId);
		}

		public override PacketType type() { return PacketType.AccountInfoRequest; }
	}

	public class AccountInfoResponsePacket : Packet {
		public UInt16 maxCreatableCharacters;
		public List<CharacterInfo> characterList = new List<CharacterInfo>();
		
		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, maxCreatableCharacters);
			Serializer.serialize(stream, characterList);
		}

		public override void deserialize(Byte[] data, Int32 offset) { 
			Serializer.deserialize(data, ref offset, out maxCreatableCharacters);
			Serializer.deserialize(data, ref offset, ref characterList);
		}

		public override PacketType type() { return PacketType.AccountInfoResponse; }
	}

	public class CreateCharacterRequestPacket : Packet {
		public UInt64 accountId;
		public CharacterClass characterClass;
		public string characterName;

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, accountId);
			Serializer.serialize(stream, characterClass);
			Serializer.serialize(stream, characterName);
		}

		public override void deserialize(Byte[] data, Int32 offset) { 
			Serializer.deserialize(data, ref offset, out accountId);
			Serializer.deserialize(data, ref offset, out characterClass);
			Serializer.deserialize(data, ref offset, out characterName);
		}

		public override PacketType type() { return PacketType.CreateCharacterRequest; }
	}
	
	public class CreateCharacterResponsePacket : Packet {
		public Int16 errorCode;

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, errorCode);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out errorCode);
		}

		public override PacketType type() { return PacketType.CreateCharacterResponse; }
	}

	public class DeleteCharacterRequestPacket : Packet {
		public UInt64 characterId;

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, characterId);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out characterId);
		}

		public override PacketType type() { return PacketType.DeleteCharacterRequest; }
	};

	public class DeleteCharacterResponsePacket : Packet {
		public override PacketType type() { return PacketType.DeleteCharacterResponse; }
	};

	public class ConnectChanelRequestPacket : Packet {
		public UInt16 chanelId; 
		public UInt64 accountId;
		public UInt64 characterId;
				
		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, chanelId);
			Serializer.serialize(stream, accountId);
			Serializer.serialize(stream, characterId);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out chanelId);
			Serializer.deserialize(data, ref offset, out accountId);
			Serializer.deserialize(data, ref offset, out characterId);
		}

		public override PacketType type() { return PacketType.ConnectChanelRequest; }
	}

	public class ConnectChanelResponsePacket : Packet {
		public Dictionary<UInt64, CharacterInfo> playerTable = new Dictionary<UInt64, CharacterInfo>();

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, playerTable);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, ref playerTable);
		}

		public override PacketType type() { return PacketType.ConnectChanelResponse; }
	}
	
	public class DisconnectChanelRequestPacket : Packet {
		public override PacketType type() { return PacketType.ConnectChanelRequest; }
	}

	public class DisconnectChanelResponsePacket : Packet {
		public override PacketType type() { return PacketType.ConnectChanelResponse; }
	}

	public class NotifyConnectPlayerPacket : Packet {
		public UInt64 accountId;
		public CharacterInfo characterInfo;

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, accountId);
			Serializer.serialize(stream, characterInfo);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out accountId);
			Serializer.deserialize(data, ref offset, out characterInfo);
		}

		public override PacketType type() { return PacketType.NotifyConnectPlayer; }
	}

	public class NotifyDisconnectPlayerPacket : Packet  {
		public UInt64 accountId;

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, accountId);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out accountId);
		}

		public override PacketType type() { return PacketType.NotifyDisconnectPlayer; }
	}
	
	public class NotifyCharacterMovementPacket : Packet {
		public UInt64 accountId;
		public CharacterMovement movement;
		
		public override PacketType type() { return PacketType.NotifyCharacterMovement; }

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, accountId);
			Serializer.serialize(stream, movement);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out accountId);
			Serializer.deserialize(data, ref offset, out movement);
		}
	}

	public class NotifyCharacterActionPacket : Packet {
		public UInt64 accountId;
		public ActionType actionType;

		public override PacketType type() { return PacketType.NotifyCharacterAction; }

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, accountId);
			Serializer.serialize(stream, actionType);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out accountId);
			Serializer.deserialize(data, ref offset, out actionType);
		}
	}
}