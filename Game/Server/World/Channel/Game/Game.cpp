#include "stdafx.h"
#include "Contents/GameProcess.h"
#include "Contents/PlayerManager.h"

int _tmain() {
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		return -1;
	}

	PlayerManager::Instance().run();

	std::shared_ptr<Server> server(new IOCPServer(new GameProcess()));
	if (!server->run()) return -1;

	WSACleanup();
	return 0;
}