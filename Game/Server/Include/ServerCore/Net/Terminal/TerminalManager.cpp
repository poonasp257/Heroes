#include "stdafx.h"

TerminalManager::TerminalManager() {

}

TerminalManager::~TerminalManager() {
	for (auto itr : terminalPool) {
		auto terminal = itr.second;
		if(terminal) delete terminal;
	}
}

void TerminalManager::initialize() {
	Json json;
	bool result = json.readFile("config.json");
	if (!result) {
		SystemLogger::Log(Logger::Error, "File could not be opened!");
		// assert
		return;
	}

	Json::Document& document = json.getDocument();
	Json::Value& config = document["App"]["Terminal"];
	if (config.IsNull()) {
		SystemLogger::Log(Logger::Error, "\'Terminal\' document is not exist");
		// assert
		return;
	}

	for (auto itr = config.MemberBegin(); itr != config.MemberEnd(); ++itr) {
		std::wstring terminalName = convertToWString(itr->name.GetString());

		Terminal *terminal = new Terminal(server, terminalName);
		std::string ip = itr->value["IP"].GetString();
		int port = itr->value["Port"].GetInt();

		terminal->initialize(ip, port);
		terminalPool.push_back(std::make_pair(terminalName, terminal));
	}
}

Terminal* TerminalManager::getTerminal(const std::wstring& name) {
	for (auto& itr : terminalPool) {
		if (itr.first == name) return itr.second;
	}

	return nullptr;
}

Terminal* TerminalManager::getTerminal(int index) {
	return terminalPool[index].second;
}

void TerminalManager::run(Server *server) {
	this->server = server;
	this->initialize();
}