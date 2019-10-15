#include "stdafx.h"
#include "Session.h"

Session::Session() {
	ZeroMemory(&sessionInfo, sizeof(SessionInfo));
}

Session::~Session() {
	this->Close();
}

void Session::Accept(SOCKET socket, SOCKADDR_IN addrInfo) {
	sessionInfo.socket = socket;
	sessionInfo.addrInfo = addrInfo;
}

void Session::Close() {
	//SessionManager::GetInstance().CloseSession(this);
}

inline SOCKET& Session::GetSocket() {
	return sessionInfo.socket;
}

inline char* Session::GetClientAddress() {
	std::array<char, 16> ip;
	inet_ntop(AF_INET, &(sessionInfo.addrInfo.sin_addr), ip.data(), ip.size());

	return ip.data();
}