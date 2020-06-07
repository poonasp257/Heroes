#include "stdafx.h"
#include "Contents/MarketplaceProcess.h"

int _tmain() {
	auto server = std::make_shared<IOCPServer>(std::make_unique<MarketplaceProcess>());
	if (!server->run()) return -1;

	return 0;
}