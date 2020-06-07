#ifndef CHANNELMANAGER_PROCESS_H
#define CHANNELMANAGER_PROCESS_H

class ChannelManagerProcess : public ContentsProcess {
public:
	ChannelManagerProcess();
	~ChannelManagerProcess();

	static void GetChannelListRequest(Session* session, const Packet* rowPacket);
};
#endif