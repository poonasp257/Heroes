#include "stdafx.h"

Session::Session() : type(SessionType::Client) {
	ZeroMemory(&sessionInfo, sizeof(SessionInfo));
}

Session::~Session() {

}

bool Session::onAccept(SOCKET socket, SOCKADDR_IN addrInfo) {
	sessionInfo.socket = socket;
	sessionInfo.addrInfo = addrInfo;

	return true;
}

void Session::onClose(bool isForced) {
	if (isForced) SessionManager::Instance().forceCloseSession(this);
	else SessionManager::Instance().closeSession(this);
}

std::wstring Session::getIP() const {
	std::array<char, SIZE_16> ip;
	inet_ntop(AF_INET, &(sessionInfo.addrInfo.sin_addr), ip.data(), ip.size());

	return convertAnsiToUnicode(ip.data());
}