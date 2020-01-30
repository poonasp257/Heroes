#include "stdafx.h"

Terminal::Terminal(Server *server, const std::wstring& name) 
	: server(server), name(name), status(TerminalStatus::Stop) {

}

Terminal::~Terminal() {
	status = TerminalStatus::Stop;
}

void Terminal::initialize(const std::string& ip, int port) {
	strcpy_s(this->ip.data(), this->ip.size(), ip.c_str());
	this->port = port;

	this->run();
}

void Terminal::run() {
	processThread = std::make_unique<Thread>(new std::thread(
		&Terminal::connectProcess, this));
}

void Terminal::sendPacket(Packet *packet) {
	if (status != TerminalStatus::Ready) return;

	session.sendPacket(packet);
}

void Terminal::connectProcess() {
	session.connectTo(ip.data(), port);

	status = TerminalStatus::Ready;

	NotifyTerminalPacket packet;
	this->session.sendPacket(&packet);

	SystemLogger::Log(Logger::Info, "* [%s] terminal connect [%s]:[%d] ready",
		name.c_str(), ip.data(), port);
	
	while (true) {
		Package *package = session.onRecv(0);

		if (package == nullptr) {
			SystemLogger::Log(Logger::Warning, "! termnal [%s] disconnected !", name.c_str());
			break;
		}

		server->putPackage(package);
		Sleep(1);
	}

	status = TerminalStatus::Stop;
}