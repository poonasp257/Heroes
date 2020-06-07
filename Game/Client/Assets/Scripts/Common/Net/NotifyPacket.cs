using System;
using UnityEngine;

namespace Heroes {
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

	public class NotifyDisconnectPlayerPacket : Packet {
		public UInt64 playerId;

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, playerId);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out playerId);
		}

		public override PacketType type() { return PacketType.NotifyDisconnectPlayer; }
	}

	public class NotifyChatPacket : Packet {
		public UInt64 playerId;
		public string name;
		public string message;

		public override PacketType type() { return PacketType.NotifyChat; }

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, playerId);
			Serializer.serialize(stream, name);
			Serializer.serialize(stream, message);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out playerId);
			Serializer.deserialize(data, ref offset, out name);
			Serializer.deserialize(data, ref offset, out message);
		}
	}

	public class NotifyPlayerMovementPacket : Packet {
		public UInt64 playerId;
		public CharacterMovement movement;

		public override PacketType type() { return PacketType.NotifyPlayerMovement; }

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, playerId);
			Serializer.serialize(stream, movement);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out playerId);
			Serializer.deserialize(data, ref offset, out movement);
		}
	}

	public class NotifyPlayerActionPacket : Packet {
		public UInt64 playerId;
		public ActionType actionType;
		public CharacterMovement movement;

		public override PacketType type() { return PacketType.NotifyPlayerAction; }

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, playerId);
			Serializer.serialize(stream, actionType);
			Serializer.serialize(stream, movement);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out playerId);
			Serializer.deserialize(data, ref offset, out actionType);
			Serializer.deserialize(data, ref offset, out movement);
		}
	}
	
	public class NotifyTakeDamagePlayerPacket : Packet {
		public UInt64 zoneId;
		public UInt64 monsterId;
		public ActionType monsterActionType;
		public UInt64 playerId;
		public Int64 playerHp;

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, zoneId);
			Serializer.serialize(stream, monsterId);
			Serializer.serialize(stream, monsterActionType);
			Serializer.serialize(stream, playerId);
			Serializer.serialize(stream, playerHp);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out zoneId);
			Serializer.deserialize(data, ref offset, out monsterId);
			Serializer.deserialize(data, ref offset, out monsterActionType);
			Serializer.deserialize(data, ref offset, out playerId);
			Serializer.deserialize(data, ref offset, out playerHp);
		}

		public override PacketType type() { return PacketType.NotifyTakeDamagePlayer; }
	}

	public class NotifyPlayerRevivePacket : Packet {
		public UInt64 playerId;

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, playerId);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out playerId);
		}

		public override PacketType type() { return PacketType.NotifyPlayerRevive; }
	}

	public class NotifyPlayerDeadPacket : Packet {
		public UInt64 playerId;

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, playerId);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out playerId);
		}

		public override PacketType type() { return PacketType.NotifyPlayerDead; }
	}

	public class NotifyLevelUpPlayerPacket : Packet {
		public UInt64 playerId;
		public CharacterInfo characterInfo;

		public override PacketType type() { return PacketType.NotifyLevelUpPlayer; }

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, playerId);
			Serializer.serialize(stream, characterInfo);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out playerId);
			Serializer.deserialize(data, ref offset, out characterInfo);
		}
	}

	public class NotifyMonsterMovementPacket : Packet {
		public UInt64 zoneId;
		public UInt64 monsterId;
		public CharacterMovement movement;

		public override PacketType type() { return PacketType.NotifyMonsterMovement; }

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, zoneId);
			Serializer.serialize(stream, monsterId);
			Serializer.serialize(stream, movement);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out zoneId);
			Serializer.deserialize(data, ref offset, out monsterId);
			Serializer.deserialize(data, ref offset, out movement);
		}
	}

	public class NotifyMonsterActionPacket : Packet {
		public UInt64 zoneId;
		public UInt64 monsterId;
		public ActionType actionType;

		public override PacketType type() { return PacketType.NotifyMonsterAction; }

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, zoneId);
			Serializer.serialize(stream, monsterId);
			Serializer.serialize(stream, actionType);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out zoneId);
			Serializer.deserialize(data, ref offset, out monsterId);
			Serializer.deserialize(data, ref offset, out actionType);
		}
	}

	public class NotifyTakeDamageMonsterPacket : Packet {
		public UInt64 zoneId;
		public UInt64 monsterId;
		public UInt64 playerId;
		public Int64 hp;

		public override PacketType type() { return PacketType.NotifyTakeDamageMonster; }
		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, zoneId);
			Serializer.serialize(stream, monsterId);
			Serializer.serialize(stream, playerId);
			Serializer.serialize(stream, hp);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out zoneId);
			Serializer.deserialize(data, ref offset, out monsterId);
			Serializer.deserialize(data, ref offset, out playerId);
			Serializer.deserialize(data, ref offset, out hp);
		}
	}

	public class NotifyRespawnMonsterPacket : Packet {
		public UInt64 zoneId;
		public UInt64 monsterId;

		public override PacketType type() { return PacketType.NotifyRespawnMonster; }

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, zoneId);
			Serializer.serialize(stream, monsterId);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out zoneId);
			Serializer.deserialize(data, ref offset, out monsterId);
		}
	}

	public class NotifyLoseAggressionMonsterPacket : Packet {
		public UInt64 zoneId;
		public UInt64 monsterId;

		public override PacketType type() { return PacketType.NotifyLoseAggressionMonster; }

		public override void serialize() {
			Serializer.serialize(stream, type());
			Serializer.serialize(stream, zoneId);
			Serializer.serialize(stream, monsterId);
		}

		public override void deserialize(Byte[] data, Int32 offset) {
			Serializer.deserialize(data, ref offset, out zoneId);
			Serializer.deserialize(data, ref offset, out monsterId);
		}
	}
}