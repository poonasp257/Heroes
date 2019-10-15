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

inline size_t IOBuffer::GetTotalBytes() const {
	return totalBytes;
}

char* IOBuffer::GetBuffer() {
	return buffer.data();
}

bool IOBuffer::SetBuffer(Stream& stream) {
	this->Clear();

	if (buffer.max_size() <= stream.size()) {
		return false;
	}
;
	char *data = buffer.data();
	int32_t offset = 0;
	int32_t packetLen = sizeof(int32_t) + (int32_t)stream.size();

	memcpy_s((void*)(data + offset), buffer.max_size(),
		(void*)&packetLen, sizeof(packetLen));
	offset += sizeof(packetLen);

	memcpy_s((void*)(data + offset), buffer.max_size(),
		(void*)stream.data(), stream.size());
	offset += (int32_t)stream.size();

	totalBytes = offset;

	return true;
}

inline WSABUF IOBuffer::CreateWsabuf() {
	WSABUF wsaBuf;
	wsaBuf.buf = buffer.data() + currentBytes;
	wsaBuf.len = (ULONG)(totalBytes - currentBytes);

	return wsaBuf;
}

LPWSAOVERLAPPED IOBuffer::GetOvelapped() {
	return &overlapped;
}

IOCPSession::IOCPSession() : Session() {
}

IOCPSession::~IOCPSession() {
}

void IOCPSession::CheckError(DWORD ret) {
	if (ret == SOCKET_ERROR
		&& (WSAGetLastError() != ERROR_IO_PENDING)) {

	}
}