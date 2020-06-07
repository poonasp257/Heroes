#include "stdafx.h"
#include "Contents/ChatProcess.h"

int _tmain() {
	auto server = std::make_shared<IOCPServer>(std::make_unique<ChatProcess>());
	if (!server->run()) return -1;

	return 0;
}