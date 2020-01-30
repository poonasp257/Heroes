#ifndef CHANNELMANAGER_PROCESS_H
#define CHANNELMANAGER_PROCESS_H

class ChannelManagerProcess : public ContentsProcess {
public:
	ChannelManagerProcess();
	virtual ~ChannelManagerProcess();

	static void ChannelListRequest(Session* session, Packet* rowPacket);
};
#endif