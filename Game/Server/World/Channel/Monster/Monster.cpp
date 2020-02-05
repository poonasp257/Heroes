#include "stdafx.h"
#include "Contents/MonsterProcess.h"

int _tmain() {
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		return -1;
	}

	std::shared_ptr<Server> server(new IOCPServer(new MonsterProcess()));
	if (!server->run()) return -1;

	WSACleanup();
	return 0;
}