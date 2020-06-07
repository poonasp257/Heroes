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

void GameDBProcess::DBSearchAccountRequest(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const DBSearchAccountRequestPacket*>(rowPacket);
	auto query = std::make_unique<SearchAccountQuery>();
	query->session = session;
	query->clientId = packet->clientId;

	QueryStatement* statement = query->getStatement();
	statement->addParam(packet->accountId);
	DBManager::Instance().pushQuery(std::move(query));
}

void GameDBProcess::DBCreateAccountRequest(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const DBCreateAccountRequestPacket*>(rowPacket);
	auto query = std::make_unique<CreateAccountQuery>();
	query->session = session;
	query->clientId = packet->clientId;

	QueryStatement* statement = query->getStatement();
	statement->addParam(packet->accountId);
	statement->addParam(packet->familyName.c_str());
	DBManager::Instance().pushQuery(std::move(query));
}

void GameDBProcess::DBGetCharacterListRequest(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const DBGetCharacterListRequestPacket*>(rowPacket);
	auto query = std::make_unique<GetCharacterListQuery>();
	query->session = session;
	query->clientId = packet->clientId;

	QueryStatement* statement = query->getStatement();
	statement->addParam(packet->accountId);
	DBManager::Instance().pushQuery(std::move(query));
}

void GameDBProcess::DBChangeCharacterOrderRequest(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const DBChangeCharacterOrderRequestPacket*>(rowPacket);
	auto query = std::make_unique<ChangeCharacterOrderQuery>();
	query->session = session;
	query->clientId = packet->clientId;
	query->fromIndex = packet->fromIndex;
	query->toIndex = packet->toIndex;

	QueryStatement* statement = query->getStatement();
	statement->addParam(packet->accountId);
	statement->addParam(packet->fromIndex);
	statement->addParam(packet->toIndex);
	DBManager::Instance().pushQuery(std::move(query));
}

void GameDBProcess::DBCreateCharacterRequest(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const DBCreateCharacterRequestPacket*>(rowPacket);
	auto query = std::make_unique<CreateCharacterQuery>();
	query->session = session;
	query->clientId = packet->clientId;

	QueryStatement* statement = query->getStatement();
	statement->addParam(packet->accountId);
	statement->addParam((UInt16)packet->characterClass);
	statement->addParam(packet->characterName.c_str());
	DBManager::Instance().pushQuery(std::move(query));
}

void GameDBProcess::DBDeleteCharacterRequest(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const DBDeleteCharacterRequestPacket*>(rowPacket);
	auto query = std::make_unique<DeleteCharacterQuery>();
	query->session = session;
	query->clientId = packet->clientId;

	QueryStatement* statement = query->getStatement();
	statement->addParam(packet->accountId);
	statement->addParam(packet->characterId);
	DBManager::Instance().pushQuery(std::move(query));
}