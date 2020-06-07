#include "stdafx.h"
#include "Contents/MarketDBProcess.h"

int _tmain() {
	DBManager::Instance().run();

	auto server = std::make_shared<IOCPServer>(std::make_unique<MarketDBProcess>());
	if (!server->run()) return -1;

	return 0;
}