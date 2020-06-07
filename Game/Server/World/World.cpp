#include "stdafx.h"
#include "Contents/WorldProcess.h"
#include "Contents/World/WorldManager.h"

int _tmain() {
	if (!WorldManager::Instance().initialize()) {
		ERROR_LOG(L"WorldManager couldn't initialized");
		return -1;
	}

	if (!WorldManager::Instance().run()) {
		ERROR_LOG(L"WorldManager couldn't initialized");
		return -1;
	}

	auto server = std::make_shared<IOCPServer>(std::make_unique<WorldProcess>());
	if (!server->run()) return -1;

	return 0;
}