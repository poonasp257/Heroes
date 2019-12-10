#include "stdafx.h"
#include "DBAgentProcess.h"
#include "Query/DBQuery.h"

DBAgentProcess::DBAgentProcess() {
	registerPacketProcess(PacketType::DBAuthLoginRequest, &DBAgentProcess::DBAuthLoginRequest);
	registerPacketProcess(PacketType::DBAuthRegisterRequest, &DBAgentProcess::DBAuthRegisterRequest);
	registerPacketProcess(PacketType::DBAccountInfoRequest, &DBAgentProcess::DBAccountInfoRequest);
	registerPacketProcess(PacketType::DBCreateCharacterRequest, &DBAgentProcess::DBCreateCharacterRequest);
	registerPacketProcess(PacketType::DBDeleteCharacterRequest, &DBAgentProcess::DBDeleteCharacterRequest);
	registerPacketProcess(PacketType::DBConnectChanelRequest, &DBAgentProcess::DBConnectChanelRequest);
}

DBAgentProcess::~DBAgentProcess() {

}

void DBAgentProcess::DBAuthLoginRequest(Session *session, Packet *rowPacket) {
	DBAuthLoginRequestPacket *packet = dynamic_cast<DBAuthLoginRequestPacket*>(rowPacket);

	DBAuthLoginQuery *query = new DBAuthLoginQuery();
	query->clientId = packet->clientId;

	QueryStatement *statement = query->getStatement();
	statement->addParam(packet->id.c_str());					
	statement->addParam(packet->password.c_str());

	DBManager::Instance().pushQuery(query);
}

void DBAgentProcess::DBAuthRegisterRequest(Session *session, Packet *rowPacket) {
	DBAuthRegisterRequestPacket *packet = dynamic_cast<DBAuthRegisterRequestPacket*>(rowPacket);

	DBAuthRegisterQuery *query = new DBAuthRegisterQuery();
	query->clientId = packet->clientId;

	QueryStatement *statement = query->getStatement();
	statement->addParam(packet->id.c_str());
	statement->addParam(packet->password.c_str());

	DBManager::Instance().pushQuery(query);
}

void DBAgentProcess::DBAccountInfoRequest(Session *session, Packet *rowPacket) {
	DBAccountInfoRequestPacket *packet = dynamic_cast<DBAccountInfoRequestPacket*>(rowPacket);

	DBAccountInfoQuery *query = new DBAccountInfoQuery();
	query->clientId = packet->clientId;

	QueryStatement *statement = query->getStatement();
	statement->addParam(packet->accountId);

	DBManager::Instance().pushQuery(query);
}

void DBAgentProcess::DBCreateCharacterRequest(Session *session, Packet *rowPacket) {
	DBCreateCharacterRequestPacket *packet = dynamic_cast<DBCreateCharacterRequestPacket*>(rowPacket);

	DBCreateCharacterQuery *query = new DBCreateCharacterQuery();
	query->clientId = packet->clientId;

	QueryStatement *statement = query->getStatement();
	statement->addParam(packet->accountId);
	statement->addParam((UInt16)packet->characterClass);
	statement->addParam(packet->characterName.c_str());

	DBManager::Instance().pushQuery(query);
}

void DBAgentProcess::DBDeleteCharacterRequest(Session *session, Packet *rowPacket) {
	DBDeleteCharacterRequestPacket *packet = dynamic_cast<DBDeleteCharacterRequestPacket*>(rowPacket);

	DBDeleteCharacterQuery *query = new DBDeleteCharacterQuery();
	query->clientId = packet->clientId;

	QueryStatement *statement = query->getStatement();
	statement->addParam(packet->characterId);
	
	DBManager::Instance().pushQuery(query);
}

void DBAgentProcess::DBConnectChanelRequest(Session *session, Packet *rowPacket) {
	DBConnectChanelRequestPacket *packet = dynamic_cast<DBConnectChanelRequestPacket*>(rowPacket);
	   	
	DBCharacterInfoQuery *query = new DBCharacterInfoQuery();
	query->clientId = packet->clientId;
	query->accountId = packet->accountId;

	QueryStatement *statement = query->getStatement();
	statement->addParam(packet->characterId);

	DBManager::Instance().pushQuery(query);
}