﻿using System;
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
		public CharacterClass characterClass;
		public string characterName;

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, accessKey);
			Serializer.serialize(stream, characterClass);
			Serializer.serialize(stream, characterName);
		}

		public override void deserialize(Byte[] data, Int32 offset) { 
			Serializer.deserialize(data, ref offset, out accessKey);
			Serializer.deserialize(data, ref offset, out characterClass);
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
		public PlayerInfo playerInfo;
				
		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, accessKey);
			Serializer.serialize(stream, playerInfo);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out accessKey);
			Serializer.deserialize(data, ref offset, out playerInfo);
		}

		public override PacketType type() { return PacketType.ConnectChannelRequest; }
	}

	public class ConnectChannelResponsePacket : Packet {
		public List<KeyValuePair<UInt64, PlayerInfo>> playerList = new List<KeyValuePair<UInt64, PlayerInfo>>();

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, playerList);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, ref playerList);
		}

		public override PacketType type() { return PacketType.ConnectChannelResponse; }
	}
	
	public class DisconnectChannelRequestPacket : Packet {
		public override PacketType type() { return PacketType.ConnectChannelRequest; }
	}

	public class DisconnectChannelResponsePacket : Packet {
		public override PacketType type() { return PacketType.ConnectChannelResponse; }
	}

	public class NotifyConnectPlayerPacket : Packet {
		public PlayerInfo playerInfo;

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, playerInfo);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out playerInfo);
		}

		public override PacketType type() { return PacketType.NotifyConnectPlayer; }
	}

	public class NotifyDisconnectPlayerPacket : Packet  {
		public string accessKey;

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, accessKey);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out accessKey);
		}

		public override PacketType type() { return PacketType.NotifyDisconnectPlayer; }
	}
	
	public class NotifyCharacterMovementPacket : Packet {
		public string accessKey;
		public CharacterMovement movement;
		
		public override PacketType type() { return PacketType.NotifyCharacterMovement; }

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, accessKey);
			Serializer.serialize(stream, movement);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out accessKey);
			Serializer.deserialize(data, ref offset, out movement);
		}
	}

	public class NotifyCharacterActionPacket : Packet {
		public string accessKey;
		public ActionType actionType;

		public override PacketType type() { return PacketType.NotifyCharacterAction; }

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, accessKey);
			Serializer.serialize(stream, actionType);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out accessKey);
			Serializer.deserialize(data, ref offset, out actionType);
		}
	}
}