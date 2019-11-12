#include "stdafx.h"

Server::Server(const char *logFileName, ContentsProcess *process) 
	: logger(logFileName), process(process) {
	status = ServerStatus::Stop;

	bool result = json.readFile("config.json");
	if (!result) {
		SystemLogger::Log(Logger::Error, "File could not be opened!");
		// assert
	}
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