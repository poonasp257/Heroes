#include "stdafx.h"
#include "server.h"

Server::Server(const char *logFileName) : logger(logFileName) {
	status = ServerStatus::Stop;

	bool result = json.ReadFile("config.json");
	if (!result) {
		SystemLogger::Log("File could not be opened!", Logger::Error);
		// assert
	}
}

Server::~Server() {
	
}