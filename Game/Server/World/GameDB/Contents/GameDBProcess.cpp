#include "stdafx.h"
#include "GameDBProcess.h"
#include "Query/GameDBQuery.h"

GameDBProcess::GameDBProcess() {
	registerPacketProcess(PacketType::DBSearchAccountRequest, &GameDBProcess::DBSearchAccountRequest);
	registerPacketProcess(PacketType::DBCreateAccountRequest, &GameDBProcess::DBCreateAccountRequest); 
	registerPacketProcess(PacketType::DBGetCharacterListRequest, &GameDBProcess::DBGetCharacterListRequest);
	registerPacketProcess(PacketType::DBChangeCharacterOrderRequest, &GameDBProcess::DBChangeCharacterOrderRequest);
	registerPacketProcess(PacketType::DBCreateCharacterRequest, &GameDBProcess::DBCreateCharacterRequest);
	registerPacketProcess(PacketType::DBDeleteCharacterRequest, &GameDBProcess::DBDeleteCharacterRequest);
}

GameDBProcess::~GameDBProcess() {

}

void GameDBProcess::DBSearchAccountRequest(Session *session, Packet *rowPacket) {
	DBSearchAccountRequestPacket *packet = dynamic_cast<DBSearchAccountRequestPacket*>(rowPacket);
	SearchAccountQuery *query = new SearchAccountQuery();
	query->session = session;
	query->clientId = packet->clientId;

	QueryStatement *statement = query->getStatement();
	statement->addParam(packet->accountId);

	DBManager::Instance().pushQuery(query);
}

void GameDBProcess::DBCreateAccountRequest(Session* session, Packet* rowPacket) {
	DBCreateAccountRequestPacket *packet = dynamic_cast<DBCreateAccountRequestPacket*>(rowPacket);
	CreateAccountQuery *query = new CreateAccountQuery();
	query->session = session;
	query->clientId = packet->clientId;

	QueryStatement* statement = query->getStatement();
	statement->addParam(packet->accountId);
	statement->addParam(packet->familyName.c_str());

	DBManager::Instance().pushQuery(query);
}

void GameDBProcess::DBGetCharacterListRequest(Session* session, Packet* rowPacket) {
	DBGetCharacterListRequestPacket *packet = dynamic_cast<DBGetCharacterListRequestPacket*>(rowPacket);
	GetCharacterListQuery *query = new GetCharacterListQuery();
	query->session = session;
	query->clientId = packet->clientId;

	QueryStatement* statement = query->getStatement();
	statement->addParam(packet->accountId);

	DBManager::Instance().pushQuery(query);
}

void GameDBProcess::DBChangeCharacterOrderRequest(Session* session, Packet* rowPacket) {
	DBChangeCharacterOrderRequestPacket *packet = dynamic_cast<DBChangeCharacterOrderRequestPacket*>(rowPacket);
	ChangeCharacterOrderQuery* query = new ChangeCharacterOrderQuery();
	query->session = session;
	query->clientId = packet->clientId;
	query->fromIndex = packet->fromIndex;
	query->toIndex = packet->toIndex;

	QueryStatement* statement = query->getStatement();
	statement->addParam(packet->accountId);
	statement->addParam(packet->fromIndex);
	statement->addParam(packet->toIndex);

	DBManager::Instance().pushQuery(query);
}

void GameDBProcess::DBCreateCharacterRequest(Session *session, Packet *rowPacket) {
	DBCreateCharacterRequestPacket *packet = dynamic_cast<DBCreateCharacterRequestPacket*>(rowPacket);

	CreateCharacterQuery *query = new CreateCharacterQuery();
	query->session = session;
	query->clientId = packet->clientId;

	QueryStatement *statement = query->getStatement();
	statement->addParam(packet->accountId);
	statement->addParam((UInt16)packet->characterClass);
	statement->addParam(packet->characterName.c_str());

	DBManager::Instance().pushQuery(query);
}

void GameDBProcess::DBDeleteCharacterRequest(Session *session, Packet *rowPacket) {
	DBDeleteCharacterRequestPacket *packet = dynamic_cast<DBDeleteCharacterRequestPacket*>(rowPacket);

	DeleteCharacterQuery *query = new DeleteCharacterQuery();
	query->session = session;
	query->clientId = packet->clientId;

	QueryStatement *statement = query->getStatement();
	statement->addParam(packet->accountId);
	statement->addParam(packet->characterId);
	
	DBManager::Instance().pushQuery(query);
}