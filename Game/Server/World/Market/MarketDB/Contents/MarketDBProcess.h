#ifndef MARKETDB_PROCESS_H
#define MARKETDB_PROCESS_H

class MarketDBProcess : public ContentsProcess {
public:
	MarketDBProcess();
	virtual ~MarketDBProcess();

	//static void DBAccountInfoRequest(Session *session, Packet *rowPacket);
};
#endif