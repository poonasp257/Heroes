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

class GetChannelListRequestPacket : public Packet {
public:
	PacketType type() const { return PacketType::GetChannelListRequest; }
};

class GetChannelListResponsePacket : public Packet {
public:
	std::vector<ChannelInfo> channelList;

public:
	PacketType type() const { return PacketType::GetChannelListResponse; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << channelList;
	}

	void deSerialize(Stream& stream) {
		stream >> &channelList;
	}
};

class SearchAccountRequestPacket : public Packet {
public:
	UInt64 accountId;

public:
	PacketType type() const { return PacketType::SearchAccountRequest; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << accountId;
	}

	void deSerialize(Stream& stream) {
		stream >> &accountId;
	}
};

class SearchAccountResponsePacket : public Packet {
public:
	std::wstring familyName;
	UInt16 creatableCharactersCount;
	Byte errorCode;

public:
	PacketType type() const { return PacketType::SearchAccountResponse; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << familyName;
		stream << creatableCharactersCount;
		stream << errorCode;
	}

	void deSerialize(Stream& stream) {
		stream >> &familyName;
		stream >> &creatableCharactersCount;
		stream >> &errorCode;
	}
};

class DBSearchAccountRequestPacket : public Packet {
public:
	UInt64 clientId;
	UInt64 accountId;

public:
	PacketType type() const { return PacketType::DBSearchAccountRequest; }

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

class DBSearchAccountResponsePacket : public Packet {
public:
	UInt64 clientId;
	std::wstring familyName;
	UInt16 creatableCharactersCount;
	Byte errorCode;

public:
	PacketType type() const { return PacketType::DBSearchAccountResponse; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << clientId;
		stream << familyName;
		stream << creatableCharactersCount;
		stream << errorCode;
	}

	void deSerialize(Stream& stream) {
		stream >> &clientId;
		stream >> &familyName;
		stream >> &creatableCharactersCount;
		stream >> &errorCode;
	}
};

class CreateAccountRequestPacket : public Packet {
public:
	UInt64 accountId;
	std::wstring familyName;

public:
	PacketType type() const { return PacketType::CreateAccountRequest; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << accountId;
		stream << familyName;
	}

	void deSerialize(Stream& stream) {
		stream >> &accountId;
		stream >> &familyName;
	}
};

class CreateAccountResponsePacket : public Packet {
public:
	Byte errorCode;

public:
	PacketType type() const { return PacketType::CreateAccountResponse; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << errorCode;
	}

	void deSerialize(Stream& stream) {
		stream >> &errorCode;
	}
};

class DBCreateAccountRequestPacket : public Packet {
public:
	UInt64 clientId;
	UInt64 accountId;
	std::wstring familyName;

public:
	PacketType type() const { return PacketType::DBCreateAccountRequest; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << clientId;
		stream << accountId;
		stream << familyName;
	}

	void deSerialize(Stream& stream) {
		stream >> &clientId;
		stream >> &accountId;
		stream >> &familyName;
	}
};

class DBCreateAccountResponsePacket : public Packet {
public:
	UInt64 clientId;
	Byte errorCode;

public:
	PacketType type() const { return PacketType::DBCreateAccountResponse; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << clientId;
		stream << errorCode;
	}

	void deSerialize(Stream& stream) {
		stream >> &clientId;
		stream >> &errorCode;
	}
};

class GetCharacterListRequestPacket : public Packet {
public:
	UInt64 accountId;

public:
	PacketType type() const { return PacketType::GetCharacterListRequest; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << accountId;
	}

	void deSerialize(Stream& stream) {
		stream >> &accountId;
	}
};

class GetCharacterListResponsePacket : public Packet {
public:
	std::vector<CharacterInfo> characterList;

public:
	PacketType type() const { return PacketType::GetCharacterListResponse; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << characterList;
	}

	void deSerialize(Stream& stream) {
		stream >> &characterList;
	}
};

class DBGetCharacterListRequestPacket : public Packet {
public:
	UInt64 clientId;
	UInt64 accountId;

public:
	PacketType type() const { return PacketType::DBGetCharacterListRequest; }

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

class DBGetCharacterListResponsePacket : public Packet {
public:
	UInt64 clientId;
	std::vector<CharacterInfo> characterList;

public:
	PacketType type() const { return PacketType::DBGetCharacterListResponse; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << clientId;
		stream << characterList;
	}

	void deSerialize(Stream& stream) {
		stream >> &clientId;
		stream >> &characterList;
	}
};

class ChangeCharacterOrderRequestPacket : public Packet {
public:
	UInt64 accountId;
	UInt16 fromIndex;
	UInt16 toIndex;

public:
	PacketType type() const { return PacketType::ChangeCharacterOrderRequest; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << accountId;
		stream << fromIndex;
		stream << toIndex;
	}

	void deSerialize(Stream& stream) {
		stream >> &accountId;
		stream >> &fromIndex;
		stream >> &toIndex;
	}
};

class ChangeCharacterOrderResponsePacket : public Packet {
public:
	UInt16 fromIndex;
	UInt16 toIndex;

public:
	PacketType type() const { return PacketType::ChangeCharacterOrderResponse; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << fromIndex;
		stream << toIndex;
	}

	void deSerialize(Stream& stream) {
		stream >> &fromIndex;
		stream >> &toIndex;
	}
};

class DBChangeCharacterOrderRequestPacket : public Packet {
public:
	UInt64 clientId;
	UInt64 accountId;
	UInt16 fromIndex;
	UInt16 toIndex;

public:
	PacketType type() const { return PacketType::DBChangeCharacterOrderRequest; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << clientId;
		stream << accountId;
		stream << fromIndex;
		stream << toIndex;
	}

	void deSerialize(Stream& stream) {
		stream >> &clientId;
		stream >> &accountId;
		stream >> &fromIndex;
		stream >> &toIndex;
	}
};

class DBChangeCharacterOrderResponsePacket : public Packet {
public:
	UInt64 clientId;
	UInt16 fromIndex;
	UInt16 toIndex;

public:
	PacketType type() const { return PacketType::DBChangeCharacterOrderResponse; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << clientId;
		stream << fromIndex;
		stream << toIndex;
	}

	void deSerialize(Stream& stream) {
		stream >> &clientId;
		stream >> &fromIndex;
		stream >> &toIndex;
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
	Byte errorCode;

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
	Byte errorCode;
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
	UInt64 accountId;
	UInt64 characterId;

public:
	PacketType type() const { return PacketType::DeleteCharacterRequest; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << accountId;
		stream << characterId;
	}

	void deSerialize(Stream& stream) {
		stream >> &accountId;
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
	UInt64 accountId;
	UInt64 characterId;

public:
	PacketType type() const { return PacketType::DBDeleteCharacterRequest; }

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
	PlayerInfo playerInfo;

public:
	PacketType type() const { return PacketType::ConnectChannelRequest; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << playerInfo;
	}

	void deSerialize(Stream& stream) {
		stream >> &playerInfo;
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
	PlayerInfo playerInfo;

public:
	PacketType type() const { return PacketType::NotifyConnectPlayer; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << playerInfo;
	}

	void deSerialize(Stream& stream) {
		stream >> &playerInfo;
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