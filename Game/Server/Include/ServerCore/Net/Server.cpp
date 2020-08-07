#include "stdafx.h"

ServerState Server::state = ServerState::Stop;

Server::Server(std::unique_ptr<ContentsProcess> process) : 
	contentsProcess(std::move(process)) {
	const auto& config = ConfigManager::Instance().getConfig();
	const JsonValue& serverConfig = config["Server"];
	if (serverConfig.IsNull()) {
		ERROR_LOG(L"\'Server\' document doesn't exist");
		return;
	}
	else if (config["Name"].IsNull()) {
		ERROR_LOG(L"\'Name\' document doesn't exist");
		return;
	}

	if (serverConfig["IP"].IsNull()) {
		ERROR_LOG(L"\'Server:IP\' document doesn't exist");
		return;
	}
	else if (serverConfig["Port"].IsNull()) {
		ERROR_LOG(L"\'Server:Port\' document doesn't exist");
		return;
	}
	else if (serverConfig["ThreadCount"].IsNull()) {
		ERROR_LOG(L"\'Server:ThreadCount\' document doesn't exist");
		return;
	}

	strcpy_s(ip.data(), ip.size(), serverConfig["IP"].GetString());
	port = serverConfig["Port"].GetInt();
	workerThreadCount = serverConfig["ThreadCount"].GetInt();
	name = ConvertAnsiToUnicode(config["Name"].GetString());

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		ERROR_LOG(L"WSAStartup() failed");
		return;
	}
}

Server::~Server() {
	WSACleanup();
}

void Server::putPackage(std::unique_ptr<Package>& package) {
	if(contentsProcess == nullptr) {
		ERROR_LOG(L"process doesn't exist");
		return;
	}

	contentsProcess->putPackage(package);
}