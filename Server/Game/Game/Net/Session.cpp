#include "stdafx.h"
#include "Session.h"

Session::Session() {
	sessionInfo.socket = INVALID_SOCKET;
	memset(&(sessionInfo.addrInfo), 0, sizeof(SOCKADDR_IN));
}

Session::~Session() {
	this->Close();
}

bool Session::Accept(SOCKET socket, SOCKADDR_IN addrInfo) {
	sessionInfo.socket = socket;
	sessionInfo.addrInfo = addrInfo;
}

void Session::Close() {
	//SessionManager::GetInstance().CloseSession(this);
}

inline SOCKET& Session::GetSocket() {
	return sessionInfo.socket;
}

inline std::string Session::GetClientAddress() {

}