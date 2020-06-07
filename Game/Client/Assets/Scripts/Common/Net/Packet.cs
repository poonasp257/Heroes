using System;
using System.IO;
using System.Collections.Generic;

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
	
	public class GetChannelListRequestPacket : Packet {
		public override PacketType type() { return PacketType.GetChannelListRequest; }
	}

	public class GetChannelListResponsePacket : Packet {
		public List<ChannelInfo> channelList = new List<ChannelInfo>();

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, channelList);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, ref channelList);
		}
		
		public override PacketType type() { return PacketType.GetChannelListResponse; }
	}

	public class SearchAccountRequestPacket : Packet {
		public string accessKey;

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, accessKey);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out accessKey);
		}

		public override PacketType type() { return PacketType.SearchAccountRequest; }
	}

	public class SearchAccountResponsePacket : Packet {
		public string familyName;
		public UInt16 creatableCharactersCount;
		public Byte errorCode;
		
		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, familyName);
			Serializer.serialize(stream, creatableCharactersCount);
			Serializer.serialize(stream, errorCode);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out familyName);
			Serializer.deserialize(data, ref offset, out creatableCharactersCount);
			Serializer.deserialize(data, ref offset, out errorCode);
		}

		public override PacketType type() { return PacketType.SearchAccountResponse; }
	}

	public class CreateAccountRequestPacket : Packet {
		public string accessKey;
		public string familyName;

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, accessKey);
			Serializer.serialize(stream, familyName);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out accessKey);
			Serializer.deserialize(data, ref offset, out familyName);
		}

		public override PacketType type() { return PacketType.CreateAccountRequest; }
	}

	public class CreateAccountResponsePacket : Packet {
		public Byte errorCode;
		
		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, errorCode);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out errorCode);
		}

		public override PacketType type() { return PacketType.CreateAccountResponse; }
	}

	public class GetCharacterListRequestPacket : Packet {
		public string accessKey;
		
		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, accessKey);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out accessKey);
		}

		public override PacketType type() { return PacketType.GetCharacterListRequest; }
	}

	public class GetCharacterListResponsePacket : Packet {
		public List<CharacterInfo> characterList = new List<CharacterInfo>();
		
		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, characterList);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, ref characterList);
		}

		public override PacketType type() { return PacketType.GetCharacterListResponse; }
	}

	public class ChangeCharacterOrderRequestPacket : Packet {
		public string accessKey;
		public UInt16 fromIndex;
		public UInt16 toIndex;
		
		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, accessKey);
			Serializer.serialize(stream, fromIndex);
			Serializer.serialize(stream, toIndex);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out accessKey);
			Serializer.deserialize(data, ref offset, out fromIndex);
			Serializer.deserialize(data, ref offset, out toIndex);
		}

		public override PacketType type() { return PacketType.ChangeCharacterOrderRequest; }
	}

	public class ChangeCharacterOrderResponsePacket : Packet {
		public UInt16 fromIndex;
		public UInt16 toIndex;
		
		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, fromIndex);
			Serializer.serialize(stream, toIndex);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out fromIndex);
			Serializer.deserialize(data, ref offset, out toIndex);
		}

		public override PacketType type() { return PacketType.ChangeCharacterOrderResponse; }
	}

	public class CreateCharacterRequestPacket : Packet {
		public string accessKey;
		public CharacterClassType classType;
		public string characterName;

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, accessKey);
			Serializer.serialize(stream, classType);
			Serializer.serialize(stream, characterName);
		}

		public override void deserialize(Byte[] data, Int32 offset) { 
			Serializer.deserialize(data, ref offset, out accessKey);
			Serializer.deserialize(data, ref offset, out classType);
			Serializer.deserialize(data, ref offset, out characterName);
		}

		public override PacketType type() { return PacketType.CreateCharacterRequest; }
	}
	
	public class CreateCharacterResponsePacket : Packet {
		public Byte errorCode;

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
		public string accessKey;
		public UInt64 characterId;

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, accessKey);
			Serializer.serialize(stream, characterId);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out accessKey);
			Serializer.deserialize(data, ref offset, out characterId);
		}

		public override PacketType type() { return PacketType.DeleteCharacterRequest; }
	};

	public class DeleteCharacterResponsePacket : Packet {
		public override PacketType type() { return PacketType.DeleteCharacterResponse; }
	};

	public class ConnectChannelRequestPacket : Packet {
		public string accessKey;
		public string familyName;
		public CharacterInfo characterInfo;
				
		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, accessKey);
			Serializer.serialize(stream, familyName);
			Serializer.serialize(stream, characterInfo);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out accessKey);
			Serializer.deserialize(data, ref offset, out familyName);
			Serializer.deserialize(data, ref offset, out characterInfo);
		}

		public override PacketType type() { return PacketType.ConnectChannelRequest; }
	}

	public class ConnectChannelResponsePacket : Packet {
		public UInt64 playerId;

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, playerId);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out playerId);
		}

		public override PacketType type() { return PacketType.ConnectChannelResponse; }
	}
	
	public class DisconnectChannelRequestPacket : Packet {
		public UInt64 playerId;
		public string accessKey;

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, playerId);
			Serializer.serialize(stream, accessKey);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out playerId);
			Serializer.deserialize(data, ref offset, out accessKey);
		}

		public override PacketType type() { return PacketType.DisconnectChannelRequest; }
	}

	public class DisconnectChannelResponsePacket : Packet {
		public override PacketType type() { return PacketType.DisconnectChannelResponse; }
	}

	public class GetMonsterListPacket : Packet {
		public MonsterZoneInfo monsterZone;

		public override PacketType type() { return PacketType.GetMonsterList; }

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, monsterZone);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out monsterZone);
		}
	}

	public class TakeDamageMonsterPacket : Packet {
		public string accessKey;
		public UInt64 zoneId;
		public UInt64 monsterId;
		public UInt64 playerId;

		public override PacketType type() { return PacketType.TakeDamageMonster; }

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, accessKey);
			Serializer.serialize(stream, zoneId);
			Serializer.serialize(stream, monsterId);
			Serializer.serialize(stream, playerId);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out accessKey);
			Serializer.deserialize(data, ref offset, out zoneId);
			Serializer.deserialize(data, ref offset, out monsterId);
			Serializer.deserialize(data, ref offset, out playerId);
		}
	}

	public class GainMonsterExpPacket : Packet {
		public UInt64 playerId;
		public float exp;

		public override PacketType type() { return PacketType.GainMonsterExp; }

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, playerId);
			Serializer.serialize(stream, exp);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out playerId);
			Serializer.deserialize(data, ref offset, out exp);
		}
	}

	public class RevivePlayerRequestPacket : Packet {
		public UInt64 playerId;

		public override PacketType type() { return PacketType.RevivePlayerRequest; }

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, playerId);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out playerId);
		}
	}

	public class RevivePlayerResponsePacket : Packet {
		public override PacketType type() { return PacketType.RevivePlayerResponse; }
	}
}