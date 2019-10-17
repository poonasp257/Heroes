#include "stdafx.h"
#include "IOCPSession.h"

IOBuffer::IOBuffer() {
	ZeroMemory(&overlapped, sizeof(overlapped));
	this->Clear();
}

IOBuffer::~IOBuffer() {

}

void IOBuffer::Clear() {
	buffer.fill(0);
	totalBytes = 0;
	currentBytes = 0;
}

bool IOBuffer::NeedMoreIO(size_t transferSize) {
	currentBytes += transferSize;
	if(currentBytes < totalBytes) return true;

	return false;
}

int IOBuffer::SetTotalBytes() {
	if (totalBytes != 0) return 0;

	int32_t packetLen = 0;
	int32_t offset = 0;

	memcpy_s((void*)&packetLen, sizeof(packetLen), (void*)buffer.data(), 
		sizeof(packetLen));
	totalBytes = static_cast<size_t>(packetLen);
	offset = sizeof(packetLen);

	return offset;
}

bool IOBuffer::SetBuffer(Stream& stream) {
	this->Clear();

	if (buffer.max_size() <= stream.GetSize()) {
		return false;
	}
	
	char *data = buffer.data();
	int32_t offset = 0;
	int32_t packetLen = sizeof(int32_t) + (int32_t)stream.GetSize();

	memcpy_s((void*)(data + offset), buffer.max_size(),
		(void*)&packetLen, sizeof(packetLen));
	offset += sizeof(packetLen);

	memcpy_s((void*)(data + offset), buffer.max_size(),
		(void*)stream.GetData(), stream.GetSize());
	offset += (int32_t)stream.GetSize();

	totalBytes = offset;

	return true;
}

WSABUF IOBuffer::CreateWsabuf() {
	WSABUF wsaBuf;
	wsaBuf.buf = buffer.data() + currentBytes;
	wsaBuf.len = (ULONG)(totalBytes - currentBytes);

	return wsaBuf;
}

IOCPSession::IOCPSession() : Session() {

}

IOCPSession::~IOCPSession() {

}

void IOCPSession::Recv(WSABUF wsaBuf) {

}

bool IOCPSession::IsRecving(size_t transferSize) {

}

void IOCPSession::Send(WSABUF wsaBuf) {
	
}

void IOCPSession::OnSend(size_t transferSize) {
	
}

void IOCPSession::SendPacket(Packet *packet) {
	
}

Package* IOCPSession::OnRecv(size_t transferSize) {
	
}

void IOCPSession::RecvStanBy() {
	
}