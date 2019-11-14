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
   // CharacterClass characterClass;
    std::string id;
    std::string characterName;

public: 
     PacketType type() const { return PacketType::CreateCharacterRequest; }

     void serialize(Stream& stream) {
        stream << (UInt32)this->type();
        //stream << characterClass;
        stream << id;
        stream << characterName;
    }

     void deSerialize(Stream& stream) {
        //stream >> &characterClass;
        stream >> &id;
        stream >> &characterName;
    }
};

class CreateCharacterResponsePacket : public Packet {
public:
    BYTE result;

public:
     PacketType type() const { return PacketType::CreateCharacterResponse; }

     void serialize(Stream& stream) {
        stream << (UInt32)this->type();
        stream << result;
    }

     void deSerialize(Stream& stream) {
        stream >> &result;
    }
};

class ConnectChanelRequestPacket : public Packet {
public:
    BYTE chanel;
    std::string id;

public:
     PacketType type() const { return PacketType::ConnectChanelRequest; }

     void serialize(Stream& stream) {
        stream << (UInt32)this->type();
        stream << chanel;
        stream << id;
    }

     void deSerialize(Stream& stream) {
        stream >> &chanel;
        stream >> &id;
    }
};

class ConnectChanelResponsePacket : public Packet {
public:
    BYTE result;

public:
     PacketType type() const { return PacketType::ConnectChanelResponse; }

     void serialize(Stream& stream) {
        stream << (UInt32)this->type();
        stream << result;
    }

     void deSerialize(Stream& stream) {
        stream >> &result;
    }
};

class DisConnectChanelRequestPacket : public Packet {
public:
    BYTE chanel;
    std::string id;

public:
     PacketType type() const { return PacketType::ConnectChanelRequest; }

     void serialize(Stream& stream) {
        stream << (UInt32)this->type();
        stream << chanel;
        stream << id;
    }

     void deSerialize(Stream& stream) {
        stream >> &chanel;
        stream >> &id;
    }
};

class DisConnectChanelResponsePacket : public Packet {
public:
    BYTE result;

public:
     PacketType type() const { return PacketType::ConnectChanelResponse; }

     void serialize(Stream& stream) {
        stream << (UInt32)this->type();
        stream << result;
    }

     void deSerialize(Stream& stream) {
        stream >> &result;
    }
};

class ChattingRequestPacket : public Packet {
public:
    BYTE chatType;
    std::string id;
    std::string text;

public:
     PacketType type() const { return PacketType::ChattingRequest; }

     void serialize(Stream& stream) {
        stream << (UInt32)this->type();
        stream << chatType;
        stream << id;
        stream << text;
    }

     void deSerialize(Stream& stream) {
        stream >> &chatType;
        stream >> &id;
        stream >> &text;
    }
};

class ChattingResponsePacket : public Packet {
public:
    BYTE chatType;
    std::string id;
    std::string text;

public:
     PacketType type() const { return PacketType::ChattingResponse; }

     void serialize(Stream& stream) {
        stream << (UInt32)this->type();
        stream << chatType;
        stream << id;
        stream << text;
    }

     void deSerialize(Stream& stream) {
        stream >> &chatType;
        stream >> &id;
        stream >> &text;
    }
};

class CharacterInfoRequestPacket : public Packet {
public:
    BYTE characterNumber;
    std::string id;

public:
     PacketType type() const { return PacketType::CharacterInfoRequest; }

     void serialize(Stream& stream) {
        stream << (UInt32)this->type();
        stream << characterNumber;
        stream << id;
    }

     void deSerialize(Stream& stream) {
        stream >> &characterNumber;
        stream >> &id;
    }
};

class CharacterInfoResponsePacket : public Packet {
public:
    //CharacterInfo characterInfo;

public:
     PacketType type() const { return PacketType::CharacterInfoResponse; }

     void serialize(Stream& stream) {
        stream << (UInt32)this->type();
       //stream << characterInfo;
    }

     void deSerialize(Stream& stream) {
        //stream >> &characterInfo;
    }
};

class ApplyCharacterStatRequestPacket : public Packet {
public:
    BYTE characterNumber;
    std::string id; 
    //CharacterStat stat;

public:
     PacketType type() const { return PacketType::ApplyCharacterStatRequest; }

     void serialize(Stream& stream) {
        stream << (UInt32)this->type();
        stream << characterNumber;
        stream << id;
        //stream << stat;
    }

     void deSerialize(Stream& stream) {
        stream >> &characterNumber;
        stream >> &id;
        //stream >> &stat;
    }
};

class ApplyCharacterStatResponsePacket : public Packet {
public:
    BYTE result;

public:
     PacketType type() const { return PacketType::ApplyCharacterStatResponse; }

     void serialize(Stream& stream) {
        stream << (UInt32)this->type();
        stream << result;
    }

     void deSerialize(Stream& stream) {
        stream >> &result;
    }
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