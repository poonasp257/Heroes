#include "stdafx.h"

IOBuffer::IOBuffer() : ioType(IOType::Error) {
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

uint32_t IOBuffer::setupTotalBytes() {
	if (totalBytes != 0) return 0;

	uint32_t packetLen = 0;
	uint32_t offset = 0;

	memcpy_s((void*)&packetLen, sizeof(packetLen), (void*)buffer.data(), 
		sizeof(packetLen));
	totalBytes = static_cast<size_t>(packetLen);
	offset = sizeof(packetLen);

	return offset;
}

bool IOBuffer::setBuffer(Stream& stream) {
	this->clear();

	if (buffer.max_size() <= stream.getSize()) {
		SystemLogger::Log(Logger::Warning, "packet size is too big %d byte", stream.getSize());
		return false;
	}
	
	char *data = buffer.data();
	uint32_t offset = 0;
	uint32_t packetLen = sizeof(uint32_t) + (uint32_t)stream.getSize();

	memcpy_s((void*)(data + offset), buffer.max_size(),
		(void*)&packetLen, sizeof(packetLen));
	offset += sizeof(packetLen);

	memcpy_s((void*)(data + offset), buffer.max_size(),
		(void*)stream.getData(), stream.getSize());
	offset += (uint32_t)stream.getSize();

	totalBytes = offset;

	return true;
}

WSABUF IOBuffer::getWsaBuf() {
	WSABUF wsabuf;
	wsabuf.buf = buffer.data() + currentBytes;
	wsabuf.len = (ULONG)(totalBytes - currentBytes);

	return wsabuf;
}

IOCPSession::IOCPSession() : Session(), readBuffer(IOType::Read), 
	writeBuffer(IOType::Write) {

}

IOCPSession::~IOCPSession() {

}

void IOCPSession::recv(WSABUF wsaBuf) {
	DWORD flags = 0;
	DWORD recvBytes = 0;
	DWORD errorCode = WSARecv(sessionInfo.socket, &wsaBuf, 1, &recvBytes, &flags,
		readBuffer.getOverlapped(), NULL);
	if (errorCode == SOCKET_ERROR
		&& WSAGetLastError() != ERROR_IO_PENDING) {
		SystemLogger::Log(Logger::Error, "socket error", WSAGetLastError());
	}
}

bool IOCPSession::isRecving(size_t transferSize) {
	if (readBuffer.needMoreIO(transferSize)) {
		this->recv(readBuffer.getWsaBuf());
		return true;
	}

	return false;
}

void IOCPSession::recvStanBy() {
	readBuffer.clear();

	WSABUF wsaBuf;
	wsaBuf.buf = readBuffer.getBuffer();
	wsaBuf.len = readBuffer.getBufferSize(); 
	
	this->recv(wsaBuf);
}

void IOCPSession::send(WSABUF wsaBuf) {
	DWORD flags = 0;
	DWORD sendBytes = 0;
	DWORD errorCode = WSARecv(sessionInfo.socket, &wsaBuf, 1, &sendBytes, &flags,
		writeBuffer.getOverlapped(), NULL);
	if (errorCode == SOCKET_ERROR
		&& WSAGetLastError() != ERROR_IO_PENDING) {
		SystemLogger::Log(Logger::Error, "socket error: %d", WSAGetLastError());
	}
}

void IOCPSession::onSend(size_t transferSize) {
	if(writeBuffer.needMoreIO(transferSize)) {
		this->send(writeBuffer.getWsaBuf());
	}
}

void IOCPSession::sendPacket(Packet *packet) {
	Stream stream;
	
	packet->serialize(stream);
	if(writeBuffer.setBuffer(stream)) return;

	WSABUF wsaBuf;
	wsaBuf.buf = writeBuffer.getBuffer();
	wsaBuf.len = stream.getSize();

	this->send(wsaBuf);
	this->recvStanBy();
}

Package* IOCPSession::onRecv(size_t transferSize) {
	uint32_t offset = 0;
	offset += readBuffer.setupTotalBytes();

	if(this->isRecving(transferSize)) {
		return nullptr;
	}

	uint32_t packetDataSize = readBuffer.getTotalBytes() - sizeof(uint32_t);
	Byte *packetData = (Byte*)readBuffer.getBuffer() + offset;
	Packet *packet = PacketAnalyzer::Analyzer((const char*)packetData, packetDataSize);
	if(!packet) {
		SystemLogger::Log(Logger::Warning, "invalid packet");
		this->onClose();
		return nullptr;
	}

	Package *package = new Package(this, packet);
	return package;
}