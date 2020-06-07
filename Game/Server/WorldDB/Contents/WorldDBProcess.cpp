#include "stdafx.h"
#include "WorldDBProcess.h"
#include "Query/WorldDBQuery.h"

WorldDBProcess::WorldDBProcess() {
	registerPacketProcess(PacketType::DBSearchAccountRequest, &WorldDBProcess::DBSearchAccountRequest);
	registerPacketProcess(PacketType::DBCreateAccountRequest, &WorldDBProcess::DBCreateAccountRequest); 
	registerPacketProcess(PacketType::DBGetCharacterListRequest, &WorldDBProcess::DBGetCharacterListRequest);
	registerPacketProcess(PacketType::DBChangeCharacterOrderRequest, &WorldDBProcess::DBChangeCharacterOrderRequest);
	registerPacketProcess(PacketType::DBCreateCharacterRequest, &WorldDBProcess::DBCreateCharacterRequest);
	registerPacketProcess(PacketType::DBDeleteCharacterRequest, &WorldDBProcess::DBDeleteCharacterRequest);
	registerPacketProcess(PacketType::DBUpdateCharacterStatusRequest, &WorldDBProcess::DBUpdateCharacterStatusRequest);
}

WorldDBProcess::~WorldDBProcess() {
	   
}

void WorldDBProcess::DBSearchAccountRequest(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const DBSearchAccountRequestPacket*>(rowPacket);
	auto query = std::make_unique<SearchAccountQuery>();
	query->session = session;
	query->clientId = packet->clientId;

	QueryStatement* statement = query->getStatement();
	statement->addParam(packet->accountId);
	DBManager::Instance().pushQuery(std::move(query));
}

void WorldDBProcess::DBCreateAccountRequest(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const DBCreateAccountRequestPacket*>(rowPacket);
	auto query = std::make_unique<CreateAccountQuery>();
	query->session = session;
	query->clientId = packet->clientId;

	QueryStatement* statement = query->getStatement();
	statement->addParam(packet->accountId);
	statement->addParam(packet->familyName.c_str());
	DBManager::Instance().pushQuery(std::move(query));
}

void WorldDBProcess::DBGetCharacterListRequest(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const DBGetCharacterListRequestPacket*>(rowPacket);
	auto query = std::make_unique<GetCharacterListQuery>();
	query->session = session;
	query->clientId = packet->clientId;

	QueryStatement* statement = query->getStatement();
	statement->addParam(packet->accountId);
	DBManager::Instance().pushQuery(std::move(query));
}

void WorldDBProcess::DBChangeCharacterOrderRequest(Session* session, const Packet* rowPacket) {
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

void WorldDBProcess::DBCreateCharacterRequest(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const DBCreateCharacterRequestPacket*>(rowPacket);
	auto query = std::make_unique<CreateCharacterQuery>();
	query->session = session;
	query->clientId = packet->clientId;

	QueryStatement* statement = query->getStatement();
	statement->addParam(packet->accountId);
	statement->addParam((UInt16)packet->classType);
	statement->addParam(packet->characterName.c_str());
	statement->addParam(packet->hp);
	statement->addParam(packet->mp);
	DBManager::Instance().pushQuery(std::move(query));
}

void WorldDBProcess::DBDeleteCharacterRequest(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const DBDeleteCharacterRequestPacket*>(rowPacket);
	auto query = std::make_unique<DeleteCharacterQuery>();
	query->session = session;
	query->clientId = packet->clientId;

	QueryStatement* statement = query->getStatement();
	statement->addParam(packet->accountId);
	statement->addParam(packet->characterId);
	DBManager::Instance().pushQuery(std::move(query));
}

void WorldDBProcess::DBUpdateCharacterStatusRequest(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const DBUpdateCharacterStatusRequestPacket*>(rowPacket);
	auto query = std::make_unique<UpdateCharacterStatusQuery>();

	QueryStatement* statement = query->getStatement();
	statement->addParam(packet->accountId);
	statement->addParam(packet->characterId);
	statement->addParam(packet->level);
	statement->addParam(packet->exp);
	statement->addParam(packet->hp);
	statement->addParam(packet->mp);
	statement->addParam(packet->position);
	statement->addParam(packet->rotation);
	statement->addParam(L"벨리아 마을");
	DBManager::Instance().pushQuery(std::move(query));
}