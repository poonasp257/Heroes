#include "stdafx.h"
#include "Contents/GameProcess.h"

int _tmain() {
	auto server = std::make_shared<IOCPServer>(std::make_unique<GameProcess>());
	if (!server->run()) return -1;

	return 0;
}