#ifndef TERMINAL_H
#define TERMINAL_H

class Server;

enum class TerminalState {
	Stop,
	Running,
};

class Terminal {
private:	
	std::shared_ptr<Server>				server;
	std::wstring						name;

	std::array<char, SIZE_16>			ip;
	UInt16								port;

	TerminalState						state;
	std::shared_ptr<TerminalSession>	session;
	std::shared_ptr<Thread>				processThread;

private:
	void tryConnectProcess();
	void receivePacketProcess();

public:
	Terminal(std::shared_ptr<Server> server, const std::wstring& name);
	~Terminal();
	
	bool initialize(const std::string& ip, int port);
	bool run();

	void sendPacket(const Packet& packet);

	const wchar_t* getName() const { return name.c_str(); }
	std::wstring  getIP() { return session->getIP(); }
	UInt16		  getPort() const { return session->getPort(); }

	void setState(TerminalState state) { this->state = state; }
	TerminalState getState() const { return state; }
};
#endif