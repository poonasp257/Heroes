#ifndef LOGIN_PROCESS_H
#define LOGIN_PROCESS_H

class GameProcess : public ContentsProcess {
public:
	GameProcess();
    virtual ~GameProcess();

	static void AccountInfoRequest(Session *session, Packet *rowPacket);
	static void DBAccountInfoResponse(Session *session, Packet *rowPacket);
	static void CreateCharacterRequest(Session *session, Packet *rowPacket);
	static void DBCreateCharacterResponse(Session *session, Packet *rowPacket);
	static void DeleteCharacterRequest(Session *session, Packet *rowPacket);
	static void DBDeleteCharacterResponse(Session *session, Packet *rowPacket);
	static void ConnectChannelRequest(Session *session, Packet *rowPacket);
	static void DBConnectChannelResponse(Session *session, Packet *rowPacket);
	static void DisconnectChannelRequest(Session *session, Packet *rowPacket); 
	static void NotifyCharacterMovement(Session *session, Packet *rowPacket);
	static void NotifyCharacterAction(Session *session, Packet *rowPacket);
};
#endif