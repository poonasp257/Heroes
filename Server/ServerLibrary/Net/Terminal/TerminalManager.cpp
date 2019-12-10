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
	Json::Value& terminalObject = document["App"]["Terminal"];
	if (terminalObject.Empty()) {
		SystemLogger::Log(Logger::Error, "\'App\' document is not exist");
		// assert
		return;
	}

	for (auto itr = terminalObject.MemberBegin(); itr != terminalObject.MemberEnd(); ++itr) {
		std::string terminalName = itr->name.GetString();

		Terminal *terminal = new Terminal(server, terminalName);
		std::string ip = itr->value["IP"].GetString();
		int port = itr->value["Port"].GetInt();

		terminal->initialize(ip, port);
		terminalPool.insert(std::make_pair(terminalName, terminal));
	}
}

Terminal* TerminalManager::getTerminal(const std::string& name) {
	auto itr = terminalPool.find(name);
	if (itr == terminalPool.end()) return nullptr;

	return terminalPool[name];
}

void TerminalManager::run(Server *server) {
	this->server = server;
	this->initialize();
}