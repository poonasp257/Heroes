#ifndef PACKET_H
#define PACKET_H

class CharacterInfo {};
class CharacterStat {};
class CharcaterSkill {};
enum class CharacterClass {};

class Packet {
public:
    virtual PacketType type() const = 0;

    virtual void serialize(Stream& stream) = 0;
    virtual void deSerialize(Stream& stream) = 0;
};

class AuthLoginRequestPacket : public Packet {
public:
    std::string id;
    std::string password;

public:
    virtual PacketType type() const { return PacketType::AuthLoginRequest; }

    virtual void serialize(Stream& stream) {
        stream << (UInt32)this->type();
        stream << id;
        stream << password;
    }

    virtual void deSerialize(Stream& stream) {
        stream >> &id;
        stream >> &password;
    }
};

class AuthLoginResponsePacket : public Packet {
public:
    BYTE result;

public:
    virtual PacketType type() const { return PacketType::AuthLoginResponse; }

    virtual void serialize(Stream& stream) {
        stream << (UInt32)this->type();
        stream << result;
    }

    virtual void deSerialize(Stream& stream) {
        stream >> &result;
    }
};

class AuthRegisterRequestPacket : public Packet {
public:
    std::string id;
    std::string password;

public:
    virtual PacketType type() const { return PacketType::AuthRegisterRequest; }

    virtual void serialize(Stream& stream) {
        stream << (UInt32)this->type();
        stream << id;
        stream << password;
    }

    virtual void deSerialize(Stream& stream) {
        stream >> &id;
        stream >> &password;
    }
};

class AuthRegisterResponsePacket : public Packet {
public:
    BYTE result;

public:
    virtual PacketType type() const { return PacketType::AuthLoginResponse; }

    virtual void serialize(Stream& stream) {
        stream << (UInt32)this->type();
        stream << result;
    }

    virtual void deSerialize(Stream& stream) {
        stream >> &result;
    }
};

class AccountInfoRequestPacket : public Packet {
public:
    std::string id;

public: 
    virtual PacketType type() const { return PacketType::AccountInfoRequest; }

    virtual void serialize(Stream& stream) {
        stream << (UInt32)this->type();
        stream << id;
    }

    virtual void deSerialize(Stream& stream) {
        stream >> &id;
    }
};

class AccountInfoResponsePacket : public Packet {
public:
    std::vector<CharacterInfo> characterList;

public: 
    virtual PacketType type() const { return PacketType::AccountInfoResponse; }

    virtual void serialize(Stream& stream) {
        stream << (UInt32)this->type();
        stream << characterList;
    }

    virtual void deSerialize(Stream& stream) {
        stream >> &characterList;
    }
};

class CreateCharacterRequestPacket : public Packet {
public:
    CharacterClass characterClass;
    std::string id;
    std::string characterName;

public: 
    virtual PacketType type() const { return PacketType::CreateCharacterRequest; }

    virtual void serialize(Stream& stream) {
        stream << (UInt32)this->type();
        stream << characterClass;
        stream << id;
        stream << characterName;
    }

    virtual void deSerialize(Stream& stream) {
        stream >> &characterClass;
        stream >> &id;
        stream >> &characterName;
    }
};

class CreateCharacterResponsePacket : public Packet {
public:
    BYTE result;

public:
    virtual PacketType type() const { return PacketType::CreateCharacterResponse; }

    virtual void serialize(Stream& stream) {
        stream << (UInt32)this->type();
        stream << result;
    }

    virtual void deSerialize(Stream& stream) {
        stream >> &result;
    }
};

class ConnectChanelRequestPacket : public Packet {
public:
    BYTE chanel;
    std::string id;

public:
    virtual PacketType type() const { return PacketType::ConnectChanelRequest; }

    virtual void serialize(Stream& stream) {
        stream << (UInt32)this->type();
        stream << chanel;
        stream << id;
    }

    virtual void deSerialize(Stream& stream) {
        stream >> &chanel;
        stream >> &id;
    }
};

class ConnectChanelResponsePacket : public Packet {
public:
    BYTE result;

public:
    virtual PacketType type() const { return PacketType::ConnectChanelResponse; }

    virtual void serialize(Stream& stream) {
        stream << (UInt32)this->type();
        stream << result;
    }

    virtual void deSerialize(Stream& stream) {
        stream >> &result;
    }
};

class DisConnectChanelRequestPacket : public Packet {
public:
    BYTE chanel;
    std::string id;

public:
    virtual PacketType type() const { return PacketType::ConnectChanelRequest; }

    virtual void serialize(Stream& stream) {
        stream << (UInt32)this->type();
        stream << chanel;
        stream << id;
    }

    virtual void deSerialize(Stream& stream) {
        stream >> &chanel;
        stream >> &id;
    }
};

class DisConnectChanelResponsePacket : public Packet {
public:
    BYTE result;

public:
    virtual PacketType type() const { return PacketType::ConnectChanelResponse; }

    virtual void serialize(Stream& stream) {
        stream << (UInt32)this->type();
        stream << result;
    }

    virtual void deSerialize(Stream& stream) {
        stream >> &result;
    }
};

class ChattingRequestPacket : public Packet {
public:
    BYTE chatType;
    std::string id;
    std::string text;

public:
    virtual PacketType type() const { return PacketType::ChattingRequest; }

    virtual void serialize(Stream& stream) {
        stream << (UInt32)this->type();
        stream << chatType;
        stream << id;
        stream << text;
    }

    virtual void deSerialize(Stream& stream) {
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
    virtual PacketType type() const { return PacketType::ChattingResponse; }

    virtual void serialize(Stream& stream) {
        stream << (UInt32)this->type();
        stream << chatType;
        stream << id;
        stream << text;
    }

    virtual void deSerialize(Stream& stream) {
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
    virtual PacketType type() const { return PacketType::CharacterInfoRequest; }

    virtual void serialize(Stream& stream) {
        stream << (UInt32)this->type();
        stream << characterNumber;
        stream << id;
    }

    virtual void deSerialize(Stream& stream) {
        stream >> &characterNumber;
        stream >> &id;
    }
};

class CharacterInfoResponsePacket : public Packet {
public:
    CharacterInfo characterInfo;

public:
    virtual PacketType type() const { return PacketType::CharacterInfoResponse; }

    virtual void serialize(Stream& stream) {
        stream << (UInt32)this->type();
        stream << characterInfo;
    }

    virtual void deSerialize(Stream& stream) {
        stream >> &characterInfo;
    }
};

class ApplyCharacterStatRequestPacket : public Packet {
public:
    BYTE characterNumber;
    std::string id; 
    CharacterStat stat;

public:
    virtual PacketType type() const { return PacketType::ApplyCharacterStatRequest; }

    virtual void serialize(Stream& stream) {
        stream << (UInt32)this->type();
        stream << characterNumber;
        stream << id;
        stream << stat;
    }

    virtual void deSerialize(Stream& stream) {
        stream >> &characterNumber;
        stream >> &id;
        stream >> &stat;
    }
};

class ApplyCharacterStatResponsePacket : public Packet {
public:
    BYTE result;

public:
    virtual PacketType type() const { return PacketType::ApplyCharacterStatResponse; }

    virtual void serialize(Stream& stream) {
        stream << (UInt32)this->type();
        stream << result;
    }

    virtual void deSerialize(Stream& stream) {
        stream >> &result;
    }
};

class ExitRequestPacket : public Packet {
public:
    virtual PacketType type() const { return PacketType::ExitRequest; }

    virtual void serialize(Stream& stream) {
        stream << (UInt32)this->type();
    }

    virtual void deSerialize(Stream& stream) {}
};

class ExitResponsePacket : public Packet {
public:
    virtual PacketType type() const { return PacketType::ExitResponse; }

    virtual void serialize(Stream& stream) {
        stream << (UInt32)this->type();
    }

    virtual void deSerialize(Stream& stream) {}
};


#endif