#include "stdafx.h"
#include "server.h"

Server::Server() {
	status = ServerStatus::Stop;

	Json json;
	bool result = json.ReadFile("config.json");
	if (!result) {
		std::cerr << "File could not be opened!\n";
		std::cerr << "Error code: " << strerror(errno);
	}

	this->Initialize(json.GetDocument());
}

Server::~Server() {
	status = ServerStatus::Stop;
}

void Server::Initialize(Json::Document& document) {
	Json::Value& root = document["root"];
	//if (root.Empty()) {
	//	std::cerr << "\'root\' document is not exist.\n";
	//	return;
	//}

	strcpy_s(ip, root["IP"].GetString());
	port = root["Port"].GetInt();
	workerThreadCount = root["ThreadCount"].GetInt();

	status = ServerStatus::Initialize;

	std::cout << ip << std::endl;
	std::cout << port << std::endl;
	std::cout << workerThreadCount << std::endl;
}