#include "stdafx.h"
#include "MarketDBProcess.h"
#include "Query/DBQuery.h"

MarketDBProcess::MarketDBProcess() {
	//registerPacketProcess(PacketType::DBSearchAccountRequest, &MarketDBProcess::DBSearchAccountRequest);
}

MarketDBProcess::~MarketDBProcess() {

}

//void MarketDBProcess::DBSearchAccountRequest(Session* session, Packet* rowPacket) {
//	DBSearchAccountRequestPacket* packet = dynamic_cast<DBSearchAccountRequestPacket*>(rowPacket);
//
//	DBSearchAccountQuery* query = new DBSearchAccountQuery();
//	query->clientId = packet->clientId;
//
//	QueryStatement* statement = query->getStatement();
//	statement->addParam(packet->accountId);
//
//	DBManager::Instance().pushQuery(query);
//}