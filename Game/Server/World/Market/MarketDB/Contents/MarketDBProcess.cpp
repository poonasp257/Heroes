#include "stdafx.h"
#include "MarketDBProcess.h"
#include "Query/DBQuery.h"

MarketDBProcess::MarketDBProcess() {
	//registerPacketProcess(PacketType::DBAccountInfoRequest, &MarketDBProcess::DBAccountInfoRequest);
}

MarketDBProcess::~MarketDBProcess() {

}

//void MarketDBProcess::DBAccountInfoRequest(Session *session, Packet *rowPacket) {
//	DBAccountInfoRequestPacket *packet = dynamic_cast<DBAccountInfoRequestPacket*>(rowPacket);
//
//	DBAccountInfoQuery *query = new DBAccountInfoQuery();
//	query->clientId = packet->clientId;
//
//	QueryStatement *statement = query->getStatement();
//	statement->addParam(packet->accountId);
//
//	DBManager::Instance().pushQuery(query);
//}