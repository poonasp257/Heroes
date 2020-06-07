#ifndef GAMEDB_PROCESS_H
#define GAMEDB_PROCESS_H

class GameDBProcess : public ContentsProcess {
public:
	GameDBProcess();
	~GameDBProcess();

	static void DBSearchAccountRequest(Session* session, const Packet* rowPacket);
	static void DBCreateAccountRequest(Session* session, const Packet* rowPacket);
	static void DBGetCharacterListRequest(Session* session, const Packet* rowPacket);
	static void DBChangeCharacterOrderRequest(Session* session, const Packet* rowPacket);
	static void DBCreateCharacterRequest(Session* session, const Packet* rowPacket);
	static void DBDeleteCharacterRequest(Session* session, const Packet* rowPacket);
};
#endif