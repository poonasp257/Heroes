#include "stdafx.h"
#include "Contents/WorldDBProcess.h"

int _tmain() {
	if (!DBManager::Instance().initialize()) {
		ERROR_LOG(L"Terminal Manager initialized failed");
		return false;
	}
	if (!DBManager::Instance().run()) {
		ERROR_LOG(L"Terminal Manager couldn't start");
		return false;
	}

	auto server = std::make_shared<IOCPServer>(std::make_unique<WorldDBProcess>());
	if (!server->run()) return -1;

	return 0;
}