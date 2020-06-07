#include "stdafx.h"
#include "Contents/ChannelManagerProcess.h"

int _tmain() {
	auto server = std::make_shared<IOCPServer>(std::make_unique<ChannelManagerProcess>());
	if (!server->run()) return -1;

	return 0;
}