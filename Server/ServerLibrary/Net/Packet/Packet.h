#ifndef PACKET_H
#define PACKET_H

//class CharacterInfo {};
//class CharacterStat {};
//class CharcaterSkill {};
//enum class CharacterClass {};

class Packet {
public:
    virtual PacketType type() const = 0;

    virtual void serialize(Stream& stream) { stream << (UInt32)this->type(); }
	virtual void deSerialize(Stream& stream) { }
};

class AuthLoginRequestPacket : public Packet {
public:
    std::string id;
    std::string password;

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
	bool success;

public:
    PacketType type() const { return PacketType::AuthLoginResponse; }
	
	void serialize(Stream& stream) {
		stream << (UInt32)this->type();
		stream << success;
	}

	void deSerialize(Stream& stream) {
		stream >> &success;
	}
};

class AuthRegisterRequestPacket : public Packet {
public:
    std::string id;
    std::string password;

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
    PacketType type() const { return PacketType::AuthLoginResponse; }
};

class ChanelStatusRequestPacket : public Packet {
public:
	PacketType type() const { return PacketType::ChanelStatusRequest; }
};

class ChanelStatusResponsePacket : public Packet {
public:
	std::vector<ChanelStatus> chanelList;

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

class ConnectChanelRequestPacket : public Packet {
public:
	PacketType type() const { return PacketType::ConnectChanelRequest; }
};

class ConnectChanelResponsePacket : public Packet {
public:
	PacketType type() const { return PacketType::ConnectChanelResponse; }
};

class DisconnectChanelRequestPacket : public Packet {
public:
	PacketType type() const { return PacketType::DisconnectChanelRequest; }
};

class DisconnectChanelResponsePacket : public Packet {
public:
	PacketType type() const { return PacketType::DisconnectChanelResponse; }
};

class AccountInfoRequestPacket : public Packet {
public:
    std::string id;

public: 
     PacketType type() const { return PacketType::AccountInfoRequest; }

     void serialize(Stream& stream) {
        stream << (UInt32)this->type();
        stream << id;
    }

     void deSerialize(Stream& stream) {
        stream >> &id;
    }
};

class AccountInfoResponsePacket : public Packet {
public:
    //std::vector<CharacterInfo> characterList;

public: 
     PacketType type() const { return PacketType::AccountInfoResponse; }

     void serialize(Stream& stream) {
        stream << (UInt32)this->type();
        //stream << characterList;
    }

     void deSerialize(Stream& stream) {
        //stream >> &characterList;
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

class CharacterMoveRequestPacket : public Packet {
public:
	PacketType type() const { return PacketType::CharacterMoveRequest; }
};

class CharacterMoveResponsePacket : public Packet {
public:
	PacketType type() const { return PacketType::CharacterMoveResponse; }
};

class ExitRequestPacket : public Packet {
public:
     PacketType type() const { return PacketType::ExitRequest; }
};

class ExitResponsePacket : public Packet {
public:
     PacketType type() const { return PacketType::ExitResponse; }
};


#endif