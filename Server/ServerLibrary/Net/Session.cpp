#include "stdafx.h"

Session::Session() {
	ZeroMemory(&sessionInfo, sizeof(SessionInfo));
}

Session::~Session() {
	this->onClose();
}

bool Session::onAccept(SOCKET socket, SOCKADDR_IN addrInfo) {
	sessionInfo.socket = socket;
	sessionInfo.addrInfo = addrInfo;

	return true;
}

void Session::onClose() {
	SessionManager::Instance().closeSession(this);
}

std::string Session::getClientAddress() {
	std::array<char, 16> ip;
	inet_ntop(AF_INET, &(sessionInfo.addrInfo.sin_addr), ip.data(), ip.size());

	return ip.data();
}