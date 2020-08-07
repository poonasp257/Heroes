#include "stdafx.h"

TerminalManager::TerminalManager() {

}

TerminalManager::~TerminalManager() {
	for (auto& itr : terminalPool) {
		itr.second->setState(TerminalState::Stop);
	}
}

bool TerminalManager::initialize(std::shared_ptr<Server> server) {
	const auto& config = ConfigManager::Instance().getConfig();
	const JsonValue& terminalConfig = config["Terminal"];
	if (terminalConfig.IsNull()) {
		ERROR_LOG(L"\'Terminal\' document doesn't exist");
		return false;
	}

	for (auto itr = terminalConfig.MemberBegin(); itr != terminalConfig.MemberEnd(); ++itr) {
		std::wstring terminalName = ConvertAnsiToUnicode(itr->name.GetString());
		auto terminal = std::make_unique<Terminal>(server, terminalName);
		std::string ip = itr->value["IP"].GetString();
		int port = itr->value["Port"].GetInt();
		if (!terminal->initialize(ip, port)) {
			ERROR_LOG(L"terminal initialized failed");
			return false;
		}

		terminalPool.push_back(std::make_pair(terminalName, std::move(terminal)));
	}

	return true;
}

bool TerminalManager::run() {
	for (auto& itr : terminalPool) {
		if (!itr.second->run()) return false;
	}

	return true;
}

void TerminalManager::stopAll() {
	for (auto& itr : terminalPool) {
		itr.second->setState(TerminalState::Stop);
	}
}

Terminal* TerminalManager::getTerminal(const std::wstring& name) {
	for (auto& itr : terminalPool) {
		if (itr.first == name) return itr.second.get();
	}

	return nullptr;
}

Terminal* TerminalManager::getTerminal(int index) {
	return terminalPool[index].second.get();
}

size_t TerminalManager::getConnectedTerminalCount() const {
	size_t terminalCount = 0;
	for (const auto& itr : terminalPool) {
		const auto& terminal = itr.second;
		if (terminal->getState() == TerminalState::Running) {
			++terminalCount;
		}
	}

	return terminalCount;
}