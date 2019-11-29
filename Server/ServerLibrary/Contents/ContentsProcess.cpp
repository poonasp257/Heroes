#include "stdafx.h"

ContentsProcess::ContentsProcess() : packageQueue(new ThreadJobQueue<Package*>()){
	Json json;
	bool result = json.readFile("config.json");
	if (!result) {
		SystemLogger::Log(Logger::Error, "File could not be opened!");
		// assert
	}

	this->initialize(json.getDocument());
}

ContentsProcess::~ContentsProcess() {
	delete packageQueue;
}

void ContentsProcess::initialize(Json::Document& document) {
	Json::Value& app = document["App"];
	if (app.Empty()) {
		SystemLogger::Log(Logger::Error, "\'App\' document is not exist");
		// assert
	}

	int threadCount = app["Contents"]["ThreadCount"].GetInt();
	for (int i = 0; i < threadCount; ++i) {
		threadPool[i] = std::make_unique<Thread>(new std::thread(&ContentsProcess::process, this));
	}
}

void ContentsProcess::process() {
	while (true) {
		this->execute();
		Sleep(1);
	}
}

void ContentsProcess::run(Package *package) {
	Session *session = package->getSession();
	Packet *packet = package->getPacket();
	PacketType type = packet->type();

	auto itr = processTable.find(type);
	if (itr == processTable.end()) {
		SystemLogger::Log(Logger::Warning, "invaild packet runFunction. type[%d]", type);
		session->onClose();
		return;
	}

	PacketProcess packetProcess = itr->second;
	packetProcess(session, packet);
}

void ContentsProcess::execute() {
	Package *package = nullptr;
	packageQueue->pop(package);
	if(!package) return;
	   	
    this->run(package);
	delete package;
}

void ContentsProcess::registerPacketProcess(PacketType type, PacketProcess process) {
	processTable.insert(std::make_pair(type, process));
}

void ContentsProcess::putPackage(Package *package) {
    packageQueue->push(package);		
}    