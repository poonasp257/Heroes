#ifndef LOGIN_PROCESS_H
#define LOGIN_PROCESS_H

class Package;
class Session;
class Packet;

class MainProcess : public ContentsProcess {
private:
	static std::unordered_map<oid_t, CharacterInfo> playerTable;
	
public:
	MainProcess();
    ~MainProcess();

	static void AuthLoginRequest(Session *session, Packet *rowPacket);
	static void AuthRegisterRequest(Session *session, Packet *rowPacket);
	static void ChanelStatusRequest(Session *session, Packet *rowPacket);
	static void AccountInfoRequest(Session *session, Packet *rowPacket);
	static void ConnectChanelRequest(Session *session, Packet *rowPacket);
	static void DisconnectChanelRequest(Session *session, Packet *rowPacket); 
	static void CreateCharacterRequest(Session *session, Packet *rowPacket);
	static void DeleteCharacterRequest(Session *session, Packet *rowPacket);
	static void NotifyCharacterMovement(Session *session, Packet *rowPacket);
	static void NotifyCharacterAction(Session *session, Packet *rowPacket);
};

#endif