#include "stdafx.h"

int _tmain() {
	Server *server = new IOCPServer(new LoginProcess());

	if(!server->run()) {
		SystemLogger::Log(Logger::Error, "iocp server closed...");
		return -1;
	}

	delete server;
	return 0;
}