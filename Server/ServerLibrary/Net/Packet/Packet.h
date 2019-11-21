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
	std::wstring familyName;
	std::vector<CharacterInfo> characterList;

public:
	PacketType type() const { return PacketType::AccountInfoResponse; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << creatableCharacters;
		stream << familyName;
		stream << characterList;
	}

	void deSerialize(Stream& stream) {
		stream >> &creatableCharacters;
		stream >> &familyName;
		stream >> &characterList;
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
	Int32 characterId;
	std::wstring chanelId; // chanel..oid?

public:
	PacketType type() const { return PacketType::ConnectChanelRequest; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << characterId;
		stream << chanelId;
	}

	void deSerialize(Stream& stream) {
		stream >> &characterId;
		stream >> &chanelId;
	}
};

class ConnectChanelResponsePacket : public Packet {
public:
	CharacterStatus status;

public:
	PacketType type() const { return PacketType::ConnectChanelResponse; }

	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << status;
	}

	void deSerialize(Stream& stream) {
		stream >> &status;
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

class CharacterMoveRequestPacket : public Packet {
public:
	PacketType type() const { return PacketType::CharacterMoveRequest; }
};

class CharacterMoveResponsePacket : public Packet {
public:
	PacketType type() const { return PacketType::CharacterMoveResponse; }
};

#endif