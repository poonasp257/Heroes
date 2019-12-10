#ifndef TERMINAL_H
#define TERMINAL_H

enum class TerminalStatus {
	Stop,
	Ready,
};

class Terminal {
private:	
	Server						*server;
	std::string					name;

	std::array<char, SIZE_16> 	ip;
	int							port;

	TerminalSession				session;
	TerminalStatus				status;
	std::unique_ptr<Thread>		processThread;

private:
	void connectProcess();
	void run();

public:
	Terminal(Server *server, const std::string& name);
	~Terminal();
	
	void initialize(const std::string& ip, int port);
	void sendPacket(Packet *packet);

	const char* getIP() const { return ip.data(); }
	int			getPort() const { return port; }

	TerminalStatus getStatus() const { return status; }
};
#endif