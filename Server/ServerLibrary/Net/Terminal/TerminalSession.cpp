#include "stdafx.h"

TerminalSession::TerminalSession() : Session() {

}

TerminalSession::~TerminalSession() {

}

bool TerminalSession::connectTo(const char *ip, int port) {
	sessionInfo.socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sessionInfo.socket == INVALID_SOCKET) {
		SystemLogger::Log(Logger::Error, "! terminal socket fail");
		return false;
	}

	ZeroMemory(&sessionInfo.addrInfo, sizeof(sessionInfo.addrInfo));
	sessionInfo.addrInfo.sin_family = AF_INET;
	sessionInfo.addrInfo.sin_port = htons(port);
	inet_pton(AF_INET, ip, &(sessionInfo.addrInfo.sin_addr));
	
	int retVal = connect(sessionInfo.socket, (sockaddr*)&sessionInfo.addrInfo, sizeof(sessionInfo.addrInfo));
	if (retVal == SOCKET_ERROR) {
		SystemLogger::Log(Logger::Error, "! terminal socket connect fail");
		return false;
	}

	return true;
}

void TerminalSession::onSend(size_t transferSize) {
	//Noting
}

void TerminalSession::sendPacket(Packet *packet) {
	Stream stream;
	packet->serialize(stream);

	int32_t offset = 0;
	const size_t packetHeaderSize = sizeof(int32_t);
	int32_t packetLen = (int32_t)packetHeaderSize + (int32_t)stream.getSize();

	std::array<char, SOCKET_BUFSIZE> buffer;

	memcpy_s(buffer.data() + offset, packetLen, (void*)&packetLen, packetHeaderSize);
	offset += packetHeaderSize;

	memcpy_s(buffer.data() + offset, packetLen, stream.getData(), packetLen);
	offset += (int32_t)stream.getSize();

	send(sessionInfo.socket, buffer.data(), offset, 0);
}

Package* TerminalSession::onRecv(size_t transferSize) {
	std::array<Byte, SOCKET_BUFSIZE> rowData;
	
	int recvBytes = recv(sessionInfo.socket, (char*)rowData.data(), (int)rowData.size(), 0);
	if (recvBytes <= 0) return nullptr;
   
	int32_t offset = 0;
	int32_t packetLen = 0;

	memcpy_s((void*)&packetLen, sizeof(packetLen), (void*)rowData.data(), sizeof(packetLen));

	while (recvBytes < packetLen) {
		recvBytes += recv(sessionInfo.socket, (char*)rowData.data() + recvBytes,
			(int)rowData.size() - recvBytes, 0);
	}
	offset += sizeof(packetLen);
	
	Packet *packet = PacketAnalyzer::Analyzer((const char*)rowData.data() + offset, packetLen);
	if (packet == nullptr) return nullptr;

	Package *package = new Package(this, packet);
	return package;
}

void TerminalSession::recvStandBy() {
	//Noting
}