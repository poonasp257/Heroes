#include "stdafx.h"
#include "Contents/MonsterProcess.h"

int _tmain() {
	auto server = std::make_shared<IOCPServer>(std::make_unique<MonsterProcess>());
	if (!server->run()) return -1;

	return 0;
}