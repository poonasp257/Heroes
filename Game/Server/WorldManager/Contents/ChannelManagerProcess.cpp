#include "stdafx.h"
#include "ChannelManagerProcess.h"

ChannelManagerProcess::ChannelManagerProcess() {
	registerPacketProcess(PacketType::GetChannelListRequest, &ChannelManagerProcess::GetChannelListRequest);
}

ChannelManagerProcess::~ChannelManagerProcess() {

}

void ChannelManagerProcess::GetChannelListRequest(Session* session, const Packet* rowPacket) {
	ChannelInfo channel;
	GetChannelListResponsePacket responsePacket;
	size_t terminalCount = TerminalManager::Instance().getConnectedTerminalCount();
	for (int i = 0; i < terminalCount; ++i) {
		Terminal* terminal = TerminalManager::Instance().getTerminal(i);
		channel.name = terminal->getName();
		channel.ip = terminal->getIP();
		channel.port = terminal->getPort();
		responsePacket.channelList.push_back(channel);
	}

	session->sendPacket(responsePacket);
}