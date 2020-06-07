#include "stdafx.h"

Terminal::Terminal(std::shared_ptr<Server> server, const std::wstring& name) : 
	server(std::move(server)), 
	name(name), 
	state(TerminalState::Stop), 
	session(std::make_shared<TerminalSession>()) {
		
}

Terminal::~Terminal() {
	state = TerminalState::Stop;
}

bool Terminal::initialize(const std::string& ip, int port) {
	strcpy_s(this->ip.data(), this->ip.size(), ip.c_str());
	this->port = port;

	return true;
}

bool Terminal::run() {
	processThread = MAKE_THREAD(Terminal, receivePacketProcess);
	if (processThread == nullptr) return false;

	return true;
}

void Terminal::sendPacket(const Packet& packet) {
	if (state != TerminalState::Running) return;

	session->sendPacket(packet);
}

void Terminal::tryConnectProcess() {
	state = TerminalState::Stop;

	while (!session->connectTo(ip.data(), port)) {
		INFO_LOG(L"*try connect to [%s] terminal", name.c_str());
		Sleep(3000);
	}

	NotifyTerminalPacket packet;
	this->session->sendPacket(packet);

	INFO_LOG(L"*[%s] terminal connect ready", name.c_str());
	state = TerminalState::Running;
}

void Terminal::receivePacketProcess() {
	tryConnectProcess();
	   
	while (state != TerminalState::Stop) {
		auto package = session->onRecv(0);
		if (package == nullptr) {
			INFO_LOG(L"! termnal [%s] disconnected !", name.c_str());
			tryConnectProcess();
			continue;
		}

		server->putPackage(package);
		Sleep(1);
	}
}