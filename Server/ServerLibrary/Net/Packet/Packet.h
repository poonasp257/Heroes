#ifndef PACKET_H
#define PACKET_H

class Packet {
public:
	virtual PacketType type() const = 0;

	virtual void serialize(Stream& stream) { stream << (UInt32)this->type(); }
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

class AuthLoginRequestPacket : public Packet {
public:
	std::wstring id;
	std::wstring password;

public:
	PacketType type() const { return PacketType::AuthLoginRequest; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << id;
		stream << password;
	}

	void deSerialize(Stream& stream) {
		stream >> &id;
		stream >> &password;
	}
};

class AuthLoginResponsePacket : public Packet {
public:
	Int16  errorCode;
	UInt64 accountId;

public:
	PacketType type() const { return PacketType::AuthLoginResponse; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << errorCode;
		stream << accountId;
	}

	void deSerialize(Stream& stream) {
		stream >> &errorCode;
		stream >> &accountId;
	}
};

class AuthRegisterRequestPacket : public Packet {
public:
	std::wstring id;
	std::wstring password;

public:
	PacketType type() const { return PacketType::AuthRegisterRequest; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << id;
		stream << password;
	}

	void deSerialize(Stream& stream) {
		stream >> &id;
		stream >> &password;
	}
};

class AuthRegisterResponsePacket : public Packet {
public:
	Int16  errorCode;
	UInt64 accountId;

public:
	PacketType type() const { return PacketType::AuthRegisterResponse; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << errorCode;
		stream << accountId;
	}

	void deSerialize(Stream& stream) {
		stream >> &errorCode;
		stream >> &accountId;
	}
};

class ChanelStatusRequestPacket : public Packet {
public:
	PacketType type() const { return PacketType::ChanelStatusRequest; }
};

class ChanelStatusResponsePacket : public Packet {
public:
	std::vector<ChanelInfo> chanelList;

public:
	PacketType type() const { return PacketType::ChanelStatusResponse; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << chanelList;
	}

	void deSerialize(Stream& stream) {
		stream >> &chanelList;
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
	UInt16 creatableCharacters;
	std::unordered_map<UInt64, CharacterInfo> characterTable;

public:
	PacketType type() const { return PacketType::AccountInfoResponse; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << creatableCharacters;
		stream << characterTable;
	}

	void deSerialize(Stream& stream) {
		stream >> &creatableCharacters;
		stream >> &characterTable;
	}
};

class CreateCharacterRequestPacket : public Packet {
public:
	PacketType type() const { return PacketType::CreateCharacterRequest; }
};

class CreateCharacterResponsePacket : public Packet {
public:
	PacketType type() const { return PacketType::CreateCharacterResponse; }
};

class DeleteCharacterRequestPacket : public Packet {
public:
	PacketType type() const { return PacketType::DeleteCharacterRequest; }
};

class DeleteCharacterResponsePacket : public Packet {
public:
	PacketType type() const { return PacketType::DeleteCharacterResponse; }
};

class ConnectChanelRequestPacket : public Packet {
public:
	UInt16 chanelId;
	UInt64 accountId;
	UInt64 characterId;

public:
	PacketType type() const { return PacketType::ConnectChanelRequest; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << chanelId;
		stream << accountId;
		stream << characterId;
	}

	void deSerialize(Stream& stream) {
		stream >> &chanelId;
		stream >> &accountId;
		stream >> &characterId;
	}
};

class ConnectChanelResponsePacket : public Packet {
public:
	std::unordered_map<UInt64, CharacterInfo> playerTable;

public:
	PacketType type() const { return PacketType::ConnectChanelResponse; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << playerTable;
	}

	void deSerialize(Stream& stream) {
		stream >> &playerTable;
	}
};

class NotifyNewConnectPacket : public Packet {
public:
	UInt64 accountId;
	CharacterInfo characterInfo;

public:
	PacketType type() const { return PacketType::NotifyNewConnect; }

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

class DisconnectChanelRequestPacket : public Packet {
public:
	PacketType type() const { return PacketType::DisconnectChanelRequest; }
};

class DisconnectChanelResponsePacket : public Packet {
public:
	PacketType type() const { return PacketType::DisconnectChanelResponse; }
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