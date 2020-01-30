#ifndef MARKETPLACE_PROCESS_H
#define MARKETPLACE_PROCESS_H

class MarketplaceProcess : public ContentsProcess {
public:
	MarketplaceProcess();
	virtual ~MarketplaceProcess();

	//static void ChannelStatusRequest(Session* session, Packet* rowPacket);
};
#endif