#include "stdafx.h"
#include "ChannelManagerProcess.h"

ChannelManagerProcess::ChannelManagerProcess() {
	registerPacketProcess(PacketType::ChannelListRequest, &ChannelManagerProcess::ChannelListRequest);
}

ChannelManagerProcess::~ChannelManagerProcess() {

}

void ChannelManagerProcess::ChannelListRequest(Session *session, Packet *rowPacket) {
	ChannelListResponsePacket responsePacket;

	ChannelInfo channel;
	const int terminalCount = TerminalManager::Instance().getTerminalCount();

	for (int i = 0; i < terminalCount; ++i) {
		const Terminal* terminal = TerminalManager::Instance().getTerminal(i);
		
		channel.name = terminal->getName();
		channel.ip = terminal->getIP();
		channel.port = terminal->getPort();

		responsePacket.channelList.push_back(channel);
	}
	
	session->sendPacket(&responsePacket);
}