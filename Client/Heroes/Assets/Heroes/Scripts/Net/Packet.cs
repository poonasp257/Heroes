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
		public bool success;

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, success);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out success);
		}

		public override PacketType type() { return PacketType.AuthRegisterResponse; }
	}

	public class ChanelStatusRequestPacket : Packet {
		public override PacketType type() { return PacketType.ChanelStatusRequest; }
	}

	public class ChanelStatusResponsePacket : Packet {
		public List<ChanelStatus> chanelList = new List<ChanelStatus>();

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, chanelList);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, ref chanelList);
		}
		
		public override PacketType type() { return PacketType.ChanelStatusResponse; }
	}

	public class ConnectChanelRequestPacket : Packet {
		Int32 characterId;
		
		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, characterId);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out characterId);
		}

		public override PacketType type() { return PacketType.ConnectChanelRequest; }
	}

	public class ConnectChanelResponsePacket : Packet {
		// character transform
		// character status { hp, mp, exp, level, class... }  

		public override PacketType type() { return PacketType.ConnectChanelResponse; }
	}

	public class DisconnectChanelRequestPacket : Packet {
		public override PacketType type() { return PacketType.ConnectChanelRequest; }
	}

	public class DisconnectChanelResponsePacket : Packet {
		public override PacketType type() { return PacketType.ConnectChanelResponse; }
	}

	public class AccountInfoRequestPacket : Packet {
		public override PacketType type() { return PacketType.AccountInfoRequest; }
	}

	public class AccountInfoResponsePacket : Packet {
		List<CharacterStatus> characters;
		
		//public override void serialize() {
		//	Serializer.serialize(stream, type());
		//	Serializer.serialize(stream, characters);
		//}

		//public override void deserialize(Byte[] data, Int32 offset) {
		//	Serializer.deserialize(data, ref offset, ref characters);
		//}

		public override PacketType type() { return PacketType.AccountInfoResponse; }
	}

	public class CreateCharacterRequestPacket : Packet {
		// character name
		// character class

		public override PacketType type() { return PacketType.CreateCharacterRequest; }
	}
	
	public class CreateCharacterResponsePacket : Packet {
		// bool success
		// int errorCode..

		public override PacketType type() { return PacketType.CreateCharacterResponse; }
	}

	public class CharacterMoveRequestPacket : Packet {
		public Int32 characterId;
		public Vector3 position;
		public Vector3 rotatition;
		
		public override PacketType type() { return PacketType.CharacterMoveRequest;	}
	}

	public class CharacterMoveResponsePacket : Packet {
		public Int32 characterId;
		public Vector3 position;
		public Vector3 rotation;
		
		public override PacketType type() { return PacketType.CharacterMoveResponse; }
	}

	public class ExitRequestPacket : Packet {
		public override PacketType type() { return PacketType.ExitRequest; }
	}

	public class ExitResponsePacket : Packet {
		public override PacketType type() { return PacketType.ExitResponse; }
	}
}