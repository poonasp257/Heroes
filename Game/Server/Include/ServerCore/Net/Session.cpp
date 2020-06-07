#include "stdafx.h"

Session::Session() : 
	type(SessionType::Client) {
	ZeroMemory(&sessionInfo, sizeof(SessionInfo));
}

Session::~Session() {
	closesocket(sessionInfo.socket);
}

void Session::onAccept(SOCKET socket, SOCKADDR_IN addrInfo) {
	sessionInfo.socket = socket;
	sessionInfo.addrInfo = addrInfo;
}

std::wstring Session::getIP() const {
	std::array<char, SIZE_16> ip;
	inet_ntop(AF_INET, &(sessionInfo.addrInfo.sin_addr), ip.data(), ip.size());
	return ConvertAnsiToUnicode(ip.data());
}

void Session::onClose() {
	for (auto& pair : closeEventList) {
		pair.second();
	}
}

void Session::addCloseEvent(const std::wstring& name, std::function<void()> closeEvent) {
	if (closeEvent == nullptr) {
		WARNING_LOG(L"try to register empty event");
		return;
	}

	closeEventList.push_back(std::make_pair(name, closeEvent));
}

void Session::removeCloseEvent(const std::wstring& name) {
	auto itr = std::find_if(closeEventList.begin(), closeEventList.end(),
		[&name](const auto& pair) -> bool { return pair.first == name; });
	if (itr == closeEventList.end()) return;

	closeEventList.erase(itr);
}