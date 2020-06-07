#ifndef MARKETDB_PROCESS_H
#define MARKETDB_PROCESS_H

class MarketDBProcess : public ContentsProcess {
public:
	MarketDBProcess();
	~MarketDBProcess();

	//static void DBSearchAccountRequest(Session* session, Packet* rowPacket);
};
#endif