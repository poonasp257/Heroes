#ifndef GAMEDB_PROCESS_H
#define GAMEDB_PROCESS_H

class GameDBProcess : public ContentsProcess {
public:
	GameDBProcess();
	virtual ~GameDBProcess();

	static void DBAccountInfoRequest(Session *session, Packet *rowPacket);
	static void DBCreateCharacterRequest(Session *session, Packet *rowPacket);
	static void DBDeleteCharacterRequest(Session *session, Packet *rowPacket);
	static void DBConnectChannelRequest(Session *session, Packet *rowPacket);
};
#endif