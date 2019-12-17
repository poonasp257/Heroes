#ifndef LOGIN_PROCESS_H
#define LOGIN_PROCESS_H

class Package;
class Session;
class Packet;

class MainProcess : public ContentsProcess {
public:
	MainProcess();
    virtual ~MainProcess();

	static void AuthLoginRequest(Session *session, Packet *rowPacket);
	static void DBAuthLoginResponse(Session *session, Packet *rowPacket);
	static void AuthRegisterRequest(Session *session, Packet *rowPacket);
	static void DBAuthRegisterResponse(Session *session, Packet *rowPacket);
	static void ChanelStatusRequest(Session *session, Packet *rowPacket);
	static void AccountInfoRequest(Session *session, Packet *rowPacket);
	static void DBAccountInfoResponse(Session *session, Packet *rowPacket);
	static void CreateCharacterRequest(Session *session, Packet *rowPacket);
	static void DBCreateCharacterResponse(Session *session, Packet *rowPacket);
	static void DeleteCharacterRequest(Session *session, Packet *rowPacket);
	static void DBDeleteCharacterResponse(Session *session, Packet *rowPacket);
	static void ConnectChanelRequest(Session *session, Packet *rowPacket);
	static void DBConnectChanelResponse(Session *session, Packet *rowPacket);
	static void DisconnectChanelRequest(Session *session, Packet *rowPacket); 
	static void NotifyCharacterMovement(Session *session, Packet *rowPacket);
	static void NotifyCharacterAction(Session *session, Packet *rowPacket);
};
#endif