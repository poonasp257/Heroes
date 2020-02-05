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
		&Terminal::receivePacketProcess, this));
}

void Terminal::sendPacket(Packet *packet) {
	if (status != TerminalStatus::Ready) return;

	session.sendPacket(packet);
}

void Terminal::tryConnectProcess() {
	status = TerminalStatus::Stop;

	while (true) {
		if (session.connectTo(ip.data(), port)) break;

		SystemLogger::Log(Logger::Info, L"*try connect to [%s] terminal", name.c_str());
		Sleep(3000);
	}

	NotifyTerminalPacket packet;
	this->session.sendPacket(&packet);

	SystemLogger::Log(Logger::Info, L"*[%s] terminal connect ready", name.c_str());
	status = TerminalStatus::Ready;
}

void Terminal::receivePacketProcess() {
	tryConnectProcess();

	while (true) {
		Package *package = session.onRecv(0);

		if (package == nullptr) {
			SystemLogger::Log(Logger::Warning, L"! termnal [%s] disconnected !", name.c_str());
			tryConnectProcess();
			continue;
		}

		server->putPackage(package);
		Sleep(1);
	}

	status = TerminalStatus::Stop;
}