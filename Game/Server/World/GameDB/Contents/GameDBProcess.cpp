#include "stdafx.h"
#include "GameDBProcess.h"
#include "Query/DBQuery.h"

GameDBProcess::GameDBProcess() {
	registerPacketProcess(PacketType::DBAccountInfoRequest, &GameDBProcess::DBAccountInfoRequest);
	registerPacketProcess(PacketType::DBCreateCharacterRequest, &GameDBProcess::DBCreateCharacterRequest);
	registerPacketProcess(PacketType::DBDeleteCharacterRequest, &GameDBProcess::DBDeleteCharacterRequest);
	registerPacketProcess(PacketType::DBConnectChanelRequest, &GameDBProcess::DBConnectChanelRequest);
}

GameDBProcess::~GameDBProcess() {

}

void GameDBProcess::DBAccountInfoRequest(Session *session, Packet *rowPacket) {
	DBAccountInfoRequestPacket *packet = dynamic_cast<DBAccountInfoRequestPacket*>(rowPacket);

	DBAccountInfoQuery *query = new DBAccountInfoQuery();
	query->clientId = packet->clientId;

	QueryStatement *statement = query->getStatement();
	statement->addParam(packet->accountId);

	DBManager::Instance().pushQuery(query);
}

void GameDBProcess::DBCreateCharacterRequest(Session *session, Packet *rowPacket) {
	DBCreateCharacterRequestPacket *packet = dynamic_cast<DBCreateCharacterRequestPacket*>(rowPacket);

	DBCreateCharacterQuery *query = new DBCreateCharacterQuery();
	query->clientId = packet->clientId;

	QueryStatement *statement = query->getStatement();
	statement->addParam(packet->accountId);
	statement->addParam((UInt16)packet->characterClass);
	statement->addParam(packet->characterName.c_str());

	DBManager::Instance().pushQuery(query);
}

void GameDBProcess::DBDeleteCharacterRequest(Session *session, Packet *rowPacket) {
	DBDeleteCharacterRequestPacket *packet = dynamic_cast<DBDeleteCharacterRequestPacket*>(rowPacket);

	DBDeleteCharacterQuery *query = new DBDeleteCharacterQuery();
	query->clientId = packet->clientId;

	QueryStatement *statement = query->getStatement();
	statement->addParam(packet->characterId);
	
	DBManager::Instance().pushQuery(query);
}

void GameDBProcess::DBConnectChanelRequest(Session *session, Packet *rowPacket) {
	DBConnectChanelRequestPacket *packet = dynamic_cast<DBConnectChanelRequestPacket*>(rowPacket);
	   	
	DBCharacterInfoQuery *query = new DBCharacterInfoQuery();
	query->clientId = packet->clientId;
	query->accountId = packet->accountId;

	QueryStatement *statement = query->getStatement();
	statement->addParam(packet->characterId);

	DBManager::Instance().pushQuery(query);
}