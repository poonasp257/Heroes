#ifndef PACKET_H
#define PACKET_H

class Packet {
public:
	virtual PacketType type() const = 0;

	virtual void serialize(Stream& stream) { stream << (UInt32)this->type(); }
	virtual void deSerialize(Stream& stream) { }
};

class NotifyTerminalPacket : public Packet {
public:
	PacketType type() const { return PacketType::NotifyTerminal; }
};

class ExitRequestPacket : public Packet {
public:
	PacketType type() const { return PacketType::ExitRequest; }
};

class ExitResponsePacket : public Packet {
public:
	PacketType type() const { return PacketType::ExitResponse; }
};

class ChannelListRequestPacket : public Packet {
public:
	PacketType type() const { return PacketType::ChannelListRequest; }
};

class ChannelListResponsePacket : public Packet {
public:
	std::vector<ChannelInfo> channelList;

public:
	PacketType type() const { return PacketType::ChannelListResponse; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << channelList;
	}

	void deSerialize(Stream& stream) {
		stream >> &channelList;
	}
};

class AccountInfoRequestPacket : public Packet {
public:
	UInt64 accountId;

public:
	PacketType type() const { return PacketType::AccountInfoRequest; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << accountId;
	}

	void deSerialize(Stream& stream) {
		stream >> &accountId;
	}
};

class AccountInfoResponsePacket : public Packet {
public:
	UInt16 maxCreatableCharacters;
	std::vector<CharacterInfo> characterList;

public:
	PacketType type() const { return PacketType::AccountInfoResponse; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << maxCreatableCharacters;
		stream << characterList;
	}

	void deSerialize(Stream& stream) {
		stream >> &maxCreatableCharacters;
		stream >> &characterList;
	}
};

class DBAccountInfoRequestPacket : public Packet {
public:
	UInt64 clientId;
	UInt64 accountId;

public:
	PacketType type() const { return PacketType::DBAccountInfoRequest; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << clientId;
		stream << accountId;
	}

	void deSerialize(Stream& stream) {
		stream >> &clientId;
		stream >> &accountId;
	}
};

class DBAccountInfoResponsePacket : public Packet {
public:
	UInt64 clientId;
	UInt16 maxCreatableCharacters;
	std::vector<CharacterInfo> characterList;

public:
	PacketType type() const { return PacketType::DBAccountInfoResponse; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << clientId;
		stream << maxCreatableCharacters;
		stream << characterList;
	}

	void deSerialize(Stream& stream) {
		stream >> &clientId;
		stream >> &maxCreatableCharacters;
		stream >> &characterList;
	}
};

class CreateCharacterRequestPacket : public Packet {
public:
	UInt64 accountId;
	CharacterClass characterClass;
	std::wstring characterName;

public:
	PacketType type() const { return PacketType::CreateCharacterRequest; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << accountId;
		stream << characterClass;
		stream << characterName;
	}

	void deSerialize(Stream& stream) {
		stream >> &accountId;
		stream >> &characterClass;
		stream >> &characterName;
	}
};

class CreateCharacterResponsePacket : public Packet {
public:
	Int16 errorCode;

public:
	PacketType type() const { return PacketType::CreateCharacterResponse; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << errorCode;
	}

	void deSerialize(Stream& stream) {
		stream >> &errorCode;
	}
};

class DBCreateCharacterRequestPacket : public Packet {
public:
	UInt64 clientId;
	UInt64 accountId;
	CharacterClass characterClass;
	std::wstring characterName;

public:
	PacketType type() const { return PacketType::DBCreateCharacterRequest; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << clientId;
		stream << accountId;
		stream << characterClass;
		stream << characterName;
	}

	void deSerialize(Stream& stream) {
		stream >> &clientId;
		stream >> &accountId;
		stream >> &characterClass;
		stream >> &characterName;
	}
};

class DBCreateCharacterResponsePacket : public Packet {
public:
	Int16 errorCode;
	UInt64 clientId;

public:
	PacketType type() const { return PacketType::DBCreateCharacterResponse; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << errorCode;
		stream << clientId;
	}

	void deSerialize(Stream& stream) {
		stream >> &errorCode;
		stream >> &clientId;
	}
};

class DeleteCharacterRequestPacket : public Packet {
public:
	UInt64 characterId;

public:
	PacketType type() const { return PacketType::DeleteCharacterRequest; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << characterId;
	}

	void deSerialize(Stream& stream) {
		stream >> &characterId;
	}
};

class DeleteCharacterResponsePacket : public Packet {
public:
	PacketType type() const { return PacketType::DeleteCharacterResponse; }
};

class DBDeleteCharacterRequestPacket : public Packet {
public:
	UInt64 clientId;
	UInt64 characterId;

public:
	PacketType type() const { return PacketType::DBDeleteCharacterRequest; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << clientId;
		stream << characterId;
	}

	void deSerialize(Stream& stream) {
		stream >> &clientId;
		stream >> &characterId;
	}
};

class DBDeleteCharacterResponsePacket : public Packet {
public:
	UInt64 clientId;

public:
	PacketType type() const { return PacketType::DBDeleteCharacterResponse; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << clientId;
	}

	void deSerialize(Stream& stream) {
		stream >> &clientId;
	}
};

class ConnectChannelRequestPacket : public Packet {
public:
	UInt16 channelId;
	UInt64 accountId;
	UInt64 characterId;

public:
	PacketType type() const { return PacketType::ConnectChannelRequest; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << channelId;
		stream << accountId;
		stream << characterId;
	}

	void deSerialize(Stream& stream) {
		stream >> &channelId;
		stream >> &accountId;
		stream >> &characterId;
	}
};

class ConnectChannelResponsePacket : public Packet {
public:
	std::unordered_map<UInt64, CharacterInfo> playerTable;

public:
	PacketType type() const { return PacketType::ConnectChannelResponse; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << playerTable;
	}

	void deSerialize(Stream& stream) {
		stream >> &playerTable;
	}
};

class DBConnectChannelRequestPacket : public Packet {
public:
	UInt64 clientId;
	UInt64 accountId;
	UInt64 characterId;

public:
	PacketType type() const { return PacketType::DBConnectChannelRequest; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << clientId;
		stream << accountId;
		stream << characterId;
	}

	void deSerialize(Stream& stream) {
		stream >> &clientId;
		stream >> &accountId;
		stream >> &characterId;
	}
};

class DBConnectChannelResponsePacket : public Packet {
public:
	UInt64 clientId;
	UInt64 accountId;
	CharacterInfo characterInfo;

public:
	PacketType type() const { return PacketType::DBConnectChannelResponse; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << clientId;
		stream << accountId;
		stream << characterInfo;
	}

	void deSerialize(Stream& stream) {
		stream >> &clientId;
		stream >> &accountId;
		stream >> &characterInfo;
	}
};

class DisconnectChannelRequestPacket : public Packet {
public:
	PacketType type() const { return PacketType::DisconnectChannelRequest; }
};

class DisconnectChannelResponsePacket : public Packet {
public:
	PacketType type() const { return PacketType::DisconnectChannelResponse; }
};

class NotifyConnectPlayerPacket : public Packet {
public:
	UInt64 accountId;
	CharacterInfo characterInfo;

public:
	PacketType type() const { return PacketType::NotifyConnectPlayer; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << accountId;
		stream << characterInfo;
	}

	void deSerialize(Stream& stream) {
		stream >> &accountId;
		stream >> &characterInfo;
	}
};

class NotifyDisconnectPlayerPacket : public Packet {
public:
	UInt64 accountId;

public:
	PacketType type() const { return PacketType::NotifyDisconnectPlayer; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << accountId;
	}

	void deSerialize(Stream& stream) {
		stream >> &accountId;
	}
};

class NotifyCharacterMovementPacket : public Packet {
public:
	UInt64 accountId;
	CharacterMovement movement;

public:
	PacketType type() const { return PacketType::NotifyCharacterMovement; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << accountId;
		stream << movement;
	}

	void deSerialize(Stream& stream) {
		stream >> &accountId;
		stream >> &movement;
	}
};

class NotifyCharacterActionPacket : public Packet {
public:
	UInt64 accountId;
	ActionType actionType;

public:
	PacketType type() const { return PacketType::NotifyCharacterAction; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << accountId;
		stream << (UInt16)actionType;
	}

	void deSerialize(Stream& stream) {
		stream >> &accountId;
		stream >> (UInt16*)&actionType;
	}
};

#endif