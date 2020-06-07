#ifndef PACKET_H
#define PACKET_H

class Packet {
public:
	virtual PacketType type() const = 0;

	virtual void serialize(Stream& stream) const { stream << (UInt32)this->type(); }
	virtual void deSerialize(Stream& stream) { }
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

	void serialize(Stream& stream) const {
		stream << (UInt32)this->type();
		stream << channelList;
	}

	void deSerialize(Stream& stream) {
		stream >> &channelList;
	}
};

class SearchAccountRequestPacket : public Packet {
public:
	std::wstring accessKey;

public:
	PacketType type() const { return PacketType::SearchAccountRequest; }

	void serialize(Stream& stream) const {
		stream << (UInt32)this->type();
		stream << accessKey;
	}

	void deSerialize(Stream& stream) {
		stream >> &accessKey;
	}
};

class SearchAccountResponsePacket : public Packet {
public:
	std::wstring familyName;
	UInt16 creatableCharactersCount;
	Byte errorCode;

public:
	PacketType type() const { return PacketType::SearchAccountResponse; }

	void serialize(Stream& stream) const {
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
	objectId_t clientId;
	objectId_t accountId;

public:
	PacketType type() const { return PacketType::DBSearchAccountRequest; }

	void serialize(Stream& stream) const {
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
	objectId_t clientId;
	std::wstring familyName;
	UInt16 creatableCharactersCount;
	Byte errorCode;

public:
	PacketType type() const { return PacketType::DBSearchAccountResponse; }

	void serialize(Stream& stream) const {
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
	std::wstring accessKey;
	std::wstring familyName;

public:
	PacketType type() const { return PacketType::CreateAccountRequest; }

	void serialize(Stream& stream) const {
		stream << (UInt32)this->type();
		stream << accessKey;
		stream << familyName;
	}

	void deSerialize(Stream& stream) {
		stream >> &accessKey;
		stream >> &familyName;
	}
};

class CreateAccountResponsePacket : public Packet {
public:
	Byte errorCode;

public:
	PacketType type() const { return PacketType::CreateAccountResponse; }

	void serialize(Stream& stream) const {
		stream << (UInt32)this->type();
		stream << errorCode;
	}

	void deSerialize(Stream& stream) {
		stream >> &errorCode;
	}
};

class DBCreateAccountRequestPacket : public Packet {
public:
	objectId_t clientId;
	objectId_t accountId;
	std::wstring familyName;

public:
	PacketType type() const { return PacketType::DBCreateAccountRequest; }

	void serialize(Stream& stream) const {
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
	objectId_t clientId;
	Byte errorCode;

public:
	PacketType type() const { return PacketType::DBCreateAccountResponse; }

	void serialize(Stream& stream) const {
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
	std::wstring accessKey;

public:
	PacketType type() const { return PacketType::GetCharacterListRequest; }

	void serialize(Stream& stream) const {
		stream << (UInt32)this->type();
		stream << accessKey;
	}

	void deSerialize(Stream& stream) {
		stream >> &accessKey;
	}
};

class GetCharacterListResponsePacket : public Packet {
public:
	std::vector<CharacterInfo> characterList;

public:
	PacketType type() const { return PacketType::GetCharacterListResponse; }

	void serialize(Stream& stream) const {
		stream << (UInt32)this->type();
		stream << characterList;
	}

	void deSerialize(Stream& stream) {
		stream >> &characterList;
	}
};

class DBGetCharacterListRequestPacket : public Packet {
public:
	objectId_t clientId;
	objectId_t accountId;

public:
	PacketType type() const { return PacketType::DBGetCharacterListRequest; }

	void serialize(Stream& stream) const {
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
	objectId_t clientId;
	std::vector<CharacterInfo> characterList;

public:
	PacketType type() const { return PacketType::DBGetCharacterListResponse; }

	void serialize(Stream& stream) const {
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
	std::wstring accessKey;
	UInt16 fromIndex;
	UInt16 toIndex;

public:
	PacketType type() const { return PacketType::ChangeCharacterOrderRequest; }

	void serialize(Stream& stream) const {
		stream << (UInt32)this->type();
		stream << accessKey;
		stream << fromIndex;
		stream << toIndex;
	}

	void deSerialize(Stream& stream) {
		stream >> &accessKey;
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

	void serialize(Stream& stream) const {
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
	objectId_t clientId;
	objectId_t accountId;
	UInt16 fromIndex;
	UInt16 toIndex;

public:
	PacketType type() const { return PacketType::DBChangeCharacterOrderRequest; }

	void serialize(Stream& stream) const {
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
	objectId_t clientId;
	UInt16 fromIndex;
	UInt16 toIndex;

public:
	PacketType type() const { return PacketType::DBChangeCharacterOrderResponse; }

	void serialize(Stream& stream) const {
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
	std::wstring accessKey;
	CharacterClassType classType;
	std::wstring characterName;

public:
	PacketType type() const { return PacketType::CreateCharacterRequest; }

	void serialize(Stream& stream) const {
		stream << (UInt32)this->type();
		stream << accessKey;
		stream << classType;
		stream << characterName;
	}

	void deSerialize(Stream& stream) {
		stream >> &accessKey;
		stream >> &classType;
		stream >> &characterName;
	}
};

class CreateCharacterResponsePacket : public Packet {
public:
	Byte errorCode;

public:
	PacketType type() const { return PacketType::CreateCharacterResponse; }

	void serialize(Stream& stream) const {
		stream << (UInt32)this->type();
		stream << errorCode;
	}

	void deSerialize(Stream& stream) {
		stream >> &errorCode;
	}
};

class DBCreateCharacterRequestPacket : public Packet {
public:
	objectId_t clientId;
	objectId_t accountId;
	CharacterClassType classType;
	std::wstring characterName;
	Int64 hp;
	Int64 mp;

public:
	PacketType type() const { return PacketType::DBCreateCharacterRequest; }

	void serialize(Stream& stream) const {
		stream << (UInt32)this->type();
		stream << clientId;
		stream << accountId;
		stream << classType;
		stream << characterName;
		stream << hp;
		stream << mp;
	}

	void deSerialize(Stream& stream) {
		stream >> &clientId;
		stream >> &accountId;
		stream >> &classType;
		stream >> &characterName;
		stream >> &hp;
		stream >> &mp;
	}
};

class DBCreateCharacterResponsePacket : public Packet {
public:
	Byte errorCode;
	objectId_t clientId;

public:
	PacketType type() const { return PacketType::DBCreateCharacterResponse; }

	void serialize(Stream& stream) const {
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
	std::wstring accessKey;
	objectId_t characterId;

public:
	PacketType type() const { return PacketType::DeleteCharacterRequest; }

	void serialize(Stream& stream) const {
		stream << (UInt32)this->type();
		stream << accessKey;
		stream << characterId;
	}

	void deSerialize(Stream& stream) {
		stream >> &accessKey;
		stream >> &characterId;
	}
};

class DeleteCharacterResponsePacket : public Packet {
public:
	PacketType type() const { return PacketType::DeleteCharacterResponse; }
};

class DBDeleteCharacterRequestPacket : public Packet {
public:
	objectId_t clientId;
	objectId_t accountId;
	objectId_t characterId;

public:
	PacketType type() const { return PacketType::DBDeleteCharacterRequest; }

	void serialize(Stream& stream) const {
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
	objectId_t clientId;

public:
	PacketType type() const { return PacketType::DBDeleteCharacterResponse; }

	void serialize(Stream& stream) const {
		stream << (UInt32)this->type();
		stream << clientId;
	}

	void deSerialize(Stream& stream) {
		stream >> &clientId;
	}
};

class DBUpdateCharacterStatusRequestPacket : public Packet {
public:
	objectId_t accountId;
	objectId_t characterId;
	UInt32 level;
	float exp;
	Int64 hp;
	Int64 mp;
	Vector3 position;
	Vector3 rotation;

public:
	PacketType type() const { return PacketType::DBUpdateCharacterStatusRequest; }

	void serialize(Stream& stream) const {
		stream << (UInt32)this->type();
		stream << accountId;
		stream << characterId;
		stream << level;
		stream << exp;
		stream << hp;
		stream << mp;
		stream << position;
		stream << rotation;
	}

	void deSerialize(Stream& stream) {
		stream >> &accountId;
		stream >> &characterId;
		stream >> &level;
		stream >> &exp;
		stream >> &hp;
		stream >> &mp;
		stream >> &position;
		stream >> &rotation;
	}
};

class ConnectChannelRequestPacket : public Packet {
public:
	std::wstring accessKey;
	std::wstring familyName;
	CharacterInfo characterInfo;

public:
	PacketType type() const { return PacketType::ConnectChannelRequest; }

	void serialize(Stream& stream) const {
		stream << (UInt32)this->type();
		stream << accessKey;
		stream << familyName;
		stream << characterInfo;
	}

	void deSerialize(Stream& stream) {
		stream >> &accessKey;
		stream >> &familyName;
		stream >> &characterInfo;
	}
};

class ConnectChannelResponsePacket : public Packet {
public:
	objectId_t playerId;

public:
	PacketType type() const { return PacketType::ConnectChannelResponse; }

	void serialize(Stream& stream) const {
		stream << (UInt32)this->type();
		stream << playerId;
	}

	void deSerialize(Stream& stream) {
		stream >> &playerId;
	}
};

class DisconnectChannelRequestPacket : public Packet {
public:
	objectId_t playerId;
	std::wstring accessKey;

public:
	PacketType type() const { return PacketType::DisconnectChannelRequest; }

	void serialize(Stream& stream) const {
		stream << (UInt32)this->type();
		stream << playerId;
		stream << accessKey;
	}

	void deSerialize(Stream& stream) {
		stream >> &playerId;
		stream >> &accessKey;
	}
};

class DisconnectChannelResponsePacket : public Packet {
public:
	PacketType type() const { return PacketType::DisconnectChannelResponse; }
};

class WhisperChatPacket : public Packet {
public:
	objectId_t playerId;
	std::wstring receiverName;
	std::wstring message;

public:
	PacketType type() const { return PacketType::WhisperChat; }

	void serialize(Stream& stream) const {
		stream << (UInt32)this->type();
		stream << playerId;
		stream << receiverName;
		stream << message;
	}

	void deSerialize(Stream& stream) {
		stream >> &playerId;
		stream >> &receiverName;
		stream >> &message;
	}
};

class GetMonsterListPacket : public Packet {
public:
	MonsterZoneInfo monsterZone;

public:
	PacketType type() const { return PacketType::GetMonsterList; }
	
	void serialize(Stream& stream) const {
		stream << (UInt32)this->type();
		stream << monsterZone;
	}

	void deSerialize(Stream& stream) {
		stream >> &monsterZone;
	}
};

class TakeDamageMonsterPacket : public Packet {
public:
	std::wstring accessKey;
	objectId_t zoneId;
	objectId_t monsterId;
	objectId_t playerId;

public:
	PacketType type() const { return PacketType::TakeDamageMonster; }

	void serialize(Stream& stream) const {
		stream << (UInt32)this->type();
		stream << accessKey;
		stream << zoneId;
		stream << monsterId;
		stream << playerId;
	}

	void deSerialize(Stream& stream) {
		stream >> &accessKey;
		stream >> &zoneId;
		stream >> &monsterId;
		stream >> &playerId;
	}
};

class GainMonsterExpPacket : public Packet {
public:
	objectId_t playerId;
	float exp;

public:
	PacketType type() const { return PacketType::GainMonsterExp; }

	void serialize(Stream& stream) const {
		stream << (UInt32)this->type();
		stream << playerId;
		stream << exp;
	}

	void deSerialize(Stream& stream) {
		stream >> &playerId;
		stream >> &exp;
	}
};

class RevivePlayerRequestPacket : public Packet {
public:
	objectId_t playerId;

public:
	PacketType type() const { return PacketType::RevivePlayerRequest; }

	void serialize(Stream& stream) const {
		stream << (UInt32)this->type();
		stream << playerId;
	}

	void deSerialize(Stream& stream) {
		stream >> &playerId;
	}
};

class RevivePlayerResponsePacket : public Packet {
public:
	PacketType type() const { return PacketType::RevivePlayerResponse; }
};

#endif