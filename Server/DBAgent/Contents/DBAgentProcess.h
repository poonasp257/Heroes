#ifndef DBAGENT_PROCESS_H
#define DBAGENT_PROCESS_H

class DBAgentProcess : public ContentsProcess {
public:
	DBAgentProcess();
	virtual ~DBAgentProcess();

	static void DBAuthLoginRequest(Session *session, Packet *rowPacket);
	static void DBAuthRegisterRequest(Session *session, Packet *rowPacket);
	static void DBAccountInfoRequest(Session *session, Packet *rowPacket);
	static void DBCreateCharacterRequest(Session *session, Packet *rowPacket);
	static void DBDeleteCharacterRequest(Session *session, Packet *rowPacket);
	static void DBConnectChanelRequest(Session *session, Packet *rowPacket);
};
#endif