#include "stdafx.h"

Server::Server(const char *logFileName, ContentsProcess *process)
	: logger(logFileName), process(process) {
	status = ServerStatus::Stop;

	TerminalManager::Instance().run(this);

	Json json;
	bool result = json.readFile("config.json");
	if (!result) {
		SystemLogger::Log(Logger::Error, "File could not be opened!");
		// assert
		return;
	}

	Json::Document& document = json.getDocument();
	Json::Value& app = document["App"];
	if (app["Server"].Empty()) {
		SystemLogger::Log(Logger::Error, "\'Server\' object is not exist");
		// assert
		return;
	}

	strcpy_s(ip.data(), ip.size(), app["Server"]["IP"].GetString());
	port = app["Server"]["Port"].GetInt();
	workerThreadCount = app["Server"]["ThreadCount"].GetInt();

	std::string name = app["Name"].GetString();
	SystemLogger::Log(Logger::Info, "%s Server start on port %d", name.c_str(), port);
}

Server::~Server() {
	if(process) {
		delete process;
		process = nullptr;
	}
}

void Server::putPackage(Package *package) {
	if(!process) {
		SystemLogger::Log(Logger::Error, "process doesn't exist");
		return;
	}

	process->putPackage(package);
}