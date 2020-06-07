	#include "stdafx.h"

IOBuffer::IOBuffer() : 
	ioType(IOType::Error) {
	ZeroMemory(&overlapped, sizeof(overlapped));
	this->clear();
}

IOBuffer::IOBuffer(IOType ioType) : ioType(ioType) {
	ZeroMemory(&overlapped, sizeof(overlapped));
	this->clear();
}

IOBuffer::~IOBuffer() {

}

void IOBuffer::clear() {
	buffer.fill(0);
	totalBytes = 0;
	currentBytes = 0;
}

bool IOBuffer::needMoreIO(size_t transferSize) {
	currentBytes += transferSize;
	if(currentBytes < totalBytes) return true;

	return false;
}

int32_t IOBuffer::setupTotalBytes() {
	int32_t packetLen = 0;
	int32_t offset = 0;

	if (totalBytes == 0) {
		memcpy_s((void*)&packetLen, sizeof(packetLen), (void*)buffer.data(), sizeof(packetLen));
		PacketObfuscator::Instance().decodeHeader((Byte*)&packetLen);
		totalBytes = (int32_t)packetLen;
	}
	offset = sizeof(packetLen);

	return offset;
}

void IOBuffer::setBuffer(Stream& stream) {
	this->clear();

	int32_t offset = 0;
	const int32_t packetHeaderSize = sizeof(int32_t);
	int32_t packetLen = packetHeaderSize + (int32_t)stream.getSize();

	Byte* data = (Byte*)buffer.data();
	memcpy_s((void*)(data + offset), buffer.max_size(), (void*)&packetLen, packetHeaderSize);
	offset += packetHeaderSize;
	memcpy_s((void*)(data + offset), buffer.max_size(), (void*)stream.getData(), stream.getSize());
	offset += (int32_t)stream.getSize();
	totalBytes = offset;

	PacketObfuscator::Instance().encodeHeader(data);
	PacketObfuscator::Instance().encodeData(data, stream.getSize());
}

WSABUF IOBuffer::getWsaBuf() {
	WSABUF wsabuf;
	wsabuf.buf = buffer.data() + currentBytes;
	wsabuf.len = (ULONG)(totalBytes - currentBytes);
	return wsabuf;
}

IOCPSession::IOCPSession() : Session(), ioBuffer({ 
	{ IOType::Read, IOBuffer(IOType::Read) },
	{ IOType::Write, IOBuffer(IOType::Write) } }) {
	int opt = 1;
	setsockopt(sessionInfo.socket, IPPROTO_TCP, TCP_NODELAY, (const char*)&opt, sizeof(int));
}

IOCPSession::~IOCPSession() {

}

void IOCPSession::recv(WSABUF wsaBuf) {
	DWORD flags = 0;
	DWORD recvBytes;
	DWORD errorCode = WSARecv(sessionInfo.socket, &wsaBuf, 1, &recvBytes, &flags,
		ioBuffer[IOType::Read].getOverlapped(), NULL);
	if (errorCode == SOCKET_ERROR && 
		WSAGetLastError() != ERROR_IO_PENDING) {
		WARNING_LOG(L"socket error %d", WSAGetLastError());
		return;
	}
}

bool IOCPSession::isRecving(size_t transferSize) {
	if (ioBuffer[IOType::Read].needMoreIO(transferSize)) {
		this->recv(ioBuffer[IOType::Read].getWsaBuf());
		return true;
	}

	return false;
}

void IOCPSession::recvStandBy() {
	ioBuffer[IOType::Read].clear();

	WSABUF wsaBuf;
	wsaBuf.buf = ioBuffer[IOType::Read].getBuffer();
	wsaBuf.len = ioBuffer[IOType::Read].getBufferSize();
	this->recv(wsaBuf);
}

void IOCPSession::send(WSABUF wsaBuf) {
	DWORD flags = 0;
	DWORD sendBytes;
	DWORD errorCode = WSASend(sessionInfo.socket, &wsaBuf, 1, &sendBytes, flags,
		ioBuffer[IOType::Write].getOverlapped(), NULL);
	if (errorCode == SOCKET_ERROR
		&& WSAGetLastError() != ERROR_IO_PENDING) {
		ERROR_LOG(L"socket error: %d", WSAGetLastError());
	}
}

void IOCPSession::onSend(size_t transferSize) {
	if(ioBuffer[IOType::Write].needMoreIO(transferSize)) {
		this->send(ioBuffer[IOType::Write].getWsaBuf());
	}
}

void IOCPSession::sendPacket(const Packet& packet) {
	Stream stream;
	packet.serialize(stream);
	if (ioBuffer[IOType::Write].getBufferSize() <= stream.getSize()) {
		WARNING_LOG(L"packet size is too big %d byte", stream.getSize());
		return;
	}
	ioBuffer[IOType::Write].setBuffer(stream);

	size_t packetLen = ioBuffer[IOType::Write].getTotalBytes();
	INFO_LOG(L"send %d bytes[Type:%d]", packetLen, packet.type());

	WSABUF wsaBuf;
	wsaBuf.buf = ioBuffer[IOType::Write].getBuffer();
	wsaBuf.len = packetLen;

	this->send(wsaBuf);
	this->recvStandBy();
}

std::unique_ptr<Package> IOCPSession::onRecv(size_t transferSize) {
	int32_t offset = 0;
	offset += ioBuffer[IOType::Read].setupTotalBytes();
	if(this->isRecving(transferSize)) {
		return nullptr;
	}

	const size_t packetHeaderSize = sizeof(int32_t);
	const int32_t packetDataSize = (int32_t)(ioBuffer[IOType::Read].getTotalBytes() - packetHeaderSize);
	Byte* packetData = (Byte*)ioBuffer[IOType::Read].getBuffer();
	PacketObfuscator::Instance().decodeData(packetData, packetDataSize);
	std::unique_ptr<Packet> packet = PacketAnalyzer::Analyzer((const char*)packetData + offset, packetDataSize);
	if(!packet) {
		WARNING_LOG(L"invalid packet");
		//SessionManager::Instance().forceCloseSession(this);
		return nullptr;
	}

	size_t packetLen = packetHeaderSize + packetDataSize;
	INFO_LOG(L"received %d bytes[Type:%d]", packetLen, packet->type());

	this->recvStandBy();
	return std::make_unique<Package>(shared_from_this(), std::move(packet));
}