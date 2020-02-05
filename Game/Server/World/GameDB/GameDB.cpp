#include "stdafx.h"
#include "Contents/GameDBProcess.h"

int _tmain() {
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		return -1;
	}

	DBManager::Instance().run();

	std::shared_ptr<Server> server(new IOCPServer(new GameDBProcess()));
	if (!server->run()) return -1;

	WSACleanup();
	return 0;
}