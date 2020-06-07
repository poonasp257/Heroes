#ifndef NOTIFY_PACKET_H
#define NOTIFY_PACKET_H

class NotifyTerminalPacket : public Packet {
public:
	PacketType type() const { return PacketType::NotifyTerminal; }
};

class NotifyConnectPlayerPacket : public Packet {
public:
	PlayerInfo playerInfo;

public:
	PacketType type() const { return PacketType::NotifyConnectPlayer; }

	void serialize(Stream& stream) const {
		stream << (UInt32)this->type();
		stream << playerInfo;
	}

	void deSerialize(Stream& stream) {
		stream >> &playerInfo;
	}
};

class NotifyChatPacket : public Packet {
public:
	objectId_t playerId;
	std::wstring name;
	std::wstring message;

public:
	PacketType type() const { return PacketType::NotifyChat; }

	void serialize(Stream& stream) const {
		stream << (UInt32)this->type();
		stream << playerId;
		stream << name;
		stream << message;
	}

	void deSerialize(Stream& stream) {
		stream >> &playerId;
		stream >> &name;
		stream >> &message;
	}
};

class NotifyDisconnectPlayerPacket : public Packet {
public:
	objectId_t playerId;

public:
	PacketType type() const { return PacketType::NotifyDisconnectPlayer; }

	void serialize(Stream& stream) const {
		stream << (UInt32)this->type();
		stream << playerId;
	}

	void deSerialize(Stream& stream) {
		stream >> &playerId;
	}
};

class NotifyPlayerMovementPacket : public Packet {
public:
	objectId_t playerId;
	CharacterMovement movement;

public:
	PacketType type() const { return PacketType::NotifyPlayerMovement; }

	void serialize(Stream& stream) const {
		stream << (UInt32)this->type();
		stream << playerId;
		stream << movement;
	}

	void deSerialize(Stream& stream) {
		stream >> &playerId;
		stream >> &movement;
	}
};

class NotifyPlayerActionPacket : public Packet {
public:
	objectId_t playerId;
	ActionType actionType;
	CharacterMovement movement;

public:
	PacketType type() const { return PacketType::NotifyPlayerAction; }

	void serialize(Stream& stream) const {
		stream << (UInt32)this->type();
		stream << playerId;
		stream << (UInt16)actionType;
		stream << movement;
	}

	void deSerialize(Stream& stream) {
		stream >> &playerId;
		stream >> (UInt16*)&actionType;
		stream >> &movement;
	}
};

class NotifyTakeDamagePlayerPacket : public Packet {
public:
	objectId_t zoneId;
	objectId_t monsterId;
	ActionType monsterActionType;
	objectId_t playerId;
	Int64 playerHp;

public:
	PacketType type() const { return PacketType::NotifyTakeDamagePlayer; }

	void serialize(Stream& stream) const {
		stream << (UInt32)this->type();
		stream << zoneId;
		stream << monsterId;
		stream << (UInt16)monsterActionType;
		stream << playerId;
		stream << playerHp;
	}

	void deSerialize(Stream& stream) {
		stream >> &zoneId;
		stream >> &monsterId;
		stream >> (UInt16*)&monsterActionType;
		stream >> &playerId;
		stream >> &playerHp;
	}
};

class NotifyPlayerRevivePacket : public Packet {
public:
	objectId_t playerId;

public:
	PacketType type() const { return PacketType::NotifyPlayerRevive; }

	void serialize(Stream& stream) const {
		stream << (UInt32)this->type();
		stream << playerId;
	}

	void deSerialize(Stream& stream) {
		stream >> &playerId;
	}
};

class NotifyPlayerDeadPacket : public Packet {
public:
	objectId_t playerId;

public:
	PacketType type() const { return PacketType::NotifyPlayerDead; }

	void serialize(Stream& stream) const {
		stream << (UInt32)this->type();
		stream << playerId;
	}

	void deSerialize(Stream& stream) {
		stream >> &playerId;
	}
};

class NotifyLevelUpPlayerPacket : public Packet {
public:
	objectId_t playerId;
	CharacterInfo characterInfo;

public:
	PacketType type() const { return PacketType::NotifyLevelUpPlayer; }

	void serialize(Stream& stream) const {
		stream << (UInt32)this->type();
		stream << playerId;
		stream << characterInfo;
	}

	void deSerialize(Stream& stream) {
		stream >> &playerId;
		stream >> &characterInfo;
	}
};

class NotifyMonsterMovementPacket : public Packet {
public:
	objectId_t zoneId;
	objectId_t monsterId;
	CharacterMovement movement;

public:
	PacketType type() const { return PacketType::NotifyMonsterMovement; }

	void serialize(Stream& stream) const {
		stream << (UInt32)this->type();
		stream << zoneId;
		stream << monsterId;
		stream << movement;
	}

	void deSerialize(Stream& stream) {
		stream >> &zoneId;
		stream >> &monsterId;
		stream >> &movement;
	}
};

class NotifyMonsterActionPacket : public Packet {
public:
	objectId_t zoneId;
	objectId_t monsterId;
	ActionType actionType;

public:
	PacketType type() const { return PacketType::NotifyMonsterAction; }

	void serialize(Stream& stream) const {
		stream << (UInt32)this->type();
		stream << zoneId;
		stream << monsterId;
		stream << (UInt16)actionType;
	}

	void deSerialize(Stream& stream) {
		stream >> &zoneId;
		stream >> &monsterId;
		stream >> (UInt16*)&actionType;
	}
};

class NotifyTakeDamageMonsterPacket : public Packet {
public:
	objectId_t zoneId;
	objectId_t monsterId;
	objectId_t playerId;
	Int64 hp;

public:
	PacketType type() const { return PacketType::NotifyTakeDamageMonster; }

	void serialize(Stream& stream) const {
		stream << (UInt32)this->type();
		stream << zoneId;
		stream << monsterId;
		stream << playerId;
		stream << hp;
	}

	void deSerialize(Stream& stream) {
		stream >> &zoneId;
		stream >> &monsterId;
		stream >> &playerId;
		stream >> &hp;
	}
};

class NotifyRespawnMonsterPacket : public Packet {
public:
	objectId_t zoneId;
	objectId_t monsterId;

public:
	PacketType type() const { return PacketType::NotifyRespawnMonster; }

	void serialize(Stream& stream) const {
		stream << (UInt32)this->type();
		stream << zoneId;
		stream << monsterId;
	}

	void deSerialize(Stream& stream) {
		stream >> &zoneId;
		stream >> &monsterId;
	}
};

class NotifyLoseAggressionMonsterPacket : public Packet {
public:
	objectId_t zoneId;
	objectId_t monsterId;

public:
	PacketType type() const { return PacketType::NotifyLoseAggressionMonster; }

	void serialize(Stream& stream) const {
		stream << (UInt32)this->type();
		stream << zoneId;
		stream << monsterId;
	}

	void deSerialize(Stream& stream) {
		stream >> &zoneId;
		stream >> &monsterId;
	}
};

#endif