#include "stdafx.h"

ContentsProcess::ContentsProcess() : 
	threadCount(0),
	packageQueue(nullptr){
	
}

ContentsProcess::~ContentsProcess() {

}

bool ContentsProcess::initialize() {
	const auto& config = ConfigManager::Instance().getConfig();
	const Json::Value& contentsConfig = config["Contents"];
	if (contentsConfig.IsNull()) {
		ERROR_LOG(L"\'Contents\' document doesn't exist");
		return false;
	}

	if (contentsConfig["ThreadCount"].IsNull()) {
		ERROR_LOG(L"\'Database:ThreadCount\' document doesn't exist");
		return false;
	}

	threadCount = contentsConfig["ThreadCount"].GetInt();
	packageQueue = std::make_unique<SynchronizedQueue<std::unique_ptr<Package>>>(L"ContentsProcessQueue");
	this->registerPacketProcess(PacketType::NotifyTerminal, &ContentsProcess::NotifyTerminal);

	return true;
}

bool ContentsProcess::run() {
	if (threadCount <= 0) return false;

	for (int i = 0; i < threadCount; ++i) {
		threadPool.push_back(MAKE_THREAD(ContentsProcess, processThread));
	}

	return true;
}

void ContentsProcess::execute(std::unique_ptr<Package>& package) {
	Session* session = package->getSession();
	Packet* packet = package->getPacket();
	PacketType type = packet->type();

	auto itr = processTable.find(type);
	if (itr == processTable.end()) {
		WARNING_LOG(L"invaild packet runFunction. type[%d]", type);
		SessionManager::Instance().closeSession(session);
		return;
	}

	itr->second(session, packet);
}

void ContentsProcess::processThread() {
	while (Server::getState() == ServerState::Running) {
		std::unique_ptr<Package> package = nullptr;
		packageQueue->pop(package);
		if(package != nullptr) this->execute(package);

		Sleep(1);
	}
}

void ContentsProcess::registerPacketProcess(PacketType type, PacketProcess process) {
	processTable.insert(std::make_pair(type, process));
}

void ContentsProcess::putPackage(std::unique_ptr<Package>& package) {
    packageQueue->push(package);		
}    

void ContentsProcess::NotifyTerminal(Session* session, const Packet* rowPacket) {
	session->setType(SessionType::Terminal);
}