#include "stdafx.h"

TerminalSession::TerminalSession() : 
	Session() {

}

TerminalSession::~TerminalSession() {

}

bool TerminalSession::connectTo(const char* ip, int port) {
	sessionInfo.socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sessionInfo.socket == INVALID_SOCKET) {
		ERROR_LOG(L"! terminal socket create failed");
		return false;
	}

	ZeroMemory(&sessionInfo.addrInfo, sizeof(sessionInfo.addrInfo));
	sessionInfo.addrInfo.sin_family = AF_INET;
	sessionInfo.addrInfo.sin_port = htons(port);
	inet_pton(AF_INET, ip, &(sessionInfo.addrInfo.sin_addr));
	
	int retVal = connect(sessionInfo.socket, (sockaddr*)&sessionInfo.addrInfo, sizeof(sessionInfo.addrInfo));
	if (retVal == SOCKET_ERROR) {
		WARNING_LOG(L"! terminal connect failed");
		return false;
	}

	return true;
}

void TerminalSession::onSend(size_t transferSize) {
	//Nothing
}

void TerminalSession::sendPacket(const Packet& packet) {
	Stream stream;
	packet.serialize(stream);

	int32_t offset = 0;
	const size_t packetHeaderSize = sizeof(int32_t);
	int32_t packetLen = (int32_t)packetHeaderSize + (int32_t)stream.getSize();

	std::array<char, SOCKET_BUFSIZE> buffer;
	Byte* data = (Byte*)buffer.data();
	memcpy_s((void*)(data + offset), packetLen, (void*)&packetLen, packetHeaderSize);
	offset += packetHeaderSize;
	memcpy_s((void*)(data + offset), packetLen, stream.getData(), stream.getSize());
	offset += (int32_t)stream.getSize();

	PacketObfuscator::Instance().encodeHeader(data);
	PacketObfuscator::Instance().encodeData(data, stream.getSize());
	send(sessionInfo.socket, buffer.data(), offset, 0);
	//INFO_LOG(L"send %d bytes[Type:%d]", packetLen, packet.type());
}

std::unique_ptr<Package> TerminalSession::onRecv(size_t transferSize) {
	std::array<Byte, SOCKET_BUFSIZE> rowData;
	
	int recvBytes = recv(sessionInfo.socket, (char*)rowData.data(), (int)rowData.size(), 0);
	if (recvBytes <= 0) return nullptr;
   
	int32_t offset = 0;
	int32_t packetLen = 0;
	memcpy_s((void*)&packetLen, sizeof(packetLen), (void*)rowData.data(), sizeof(packetLen));
	PacketObfuscator::Instance().decodeHeader((Byte*)&packetLen);

	while (recvBytes < packetLen) {
		recvBytes += recv(sessionInfo.socket, (char*)rowData.data() + recvBytes,
			(int)rowData.size() - recvBytes, 0);
	}
	offset += sizeof(packetLen);

	PacketObfuscator::Instance().decodeData((Byte*)rowData.data(), packetLen - offset);
	std::unique_ptr<Packet> packet = PacketAnalyzer::Analyzer((const char*)rowData.data() + offset, packetLen);
	if (!packet) {
		WARNING_LOG(L"invalid packet");
		SessionManager::Instance().forceCloseSession(this);
		return nullptr;
	}

	//INFO_LOG(L"received %d bytes[Type:%d]", packetLen, packet->type());
	return std::make_unique<Package>(shared_from_this(), std::move(packet));
}

void TerminalSession::recvStandBy() {
	//Nothing
}