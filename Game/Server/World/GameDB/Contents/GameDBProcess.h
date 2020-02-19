#ifndef GAMEDB_PROCESS_H
#define GAMEDB_PROCESS_H

class GameDBProcess : public ContentsProcess {
public:
	GameDBProcess();
	virtual ~GameDBProcess();

	static void DBSearchAccountRequest(Session *session, Packet *rowPacket);
	static void DBCreateAccountRequest(Session* session, Packet* rowPacket);
	static void DBGetCharacterListRequest(Session* session, Packet* rowPacket);
	static void DBChangeCharacterOrderRequest(Session* session, Packet* rowPacket);
	static void DBCreateCharacterRequest(Session *session, Packet *rowPacket);
	static void DBDeleteCharacterRequest(Session *session, Packet *rowPacket);
};
#endif