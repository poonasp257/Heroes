#ifndef WORLD_DB_PROCESS_H
#define WORLD_DB_PROCESS_H

class WorldDBProcess : public ContentsProcess {
public:
	WorldDBProcess();
	~WorldDBProcess();

	static void DBSearchAccountRequest(Session* session, const Packet* rowPacket);
	static void DBCreateAccountRequest(Session* session, const Packet* rowPacket);
	static void DBGetCharacterListRequest(Session* session, const Packet* rowPacket);
	static void DBChangeCharacterOrderRequest(Session* session, const Packet* rowPacket);
	static void DBCreateCharacterRequest(Session* session, const Packet* rowPacket);
	static void DBDeleteCharacterRequest(Session* session, const Packet* rowPacket);
	static void DBUpdateCharacterStatusRequest(Session* session, const Packet* rowPacket);
};
#endif