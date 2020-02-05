#ifndef TERMINAL_H
#define TERMINAL_H

enum class TerminalStatus {
	Stop,
	Ready,
};

class Terminal {
private:	
	Server						*server;
	std::wstring				name;

	std::array<char, SIZE_16>	ip;
	UInt16						port;

	TerminalSession				session;
	TerminalStatus				status;
	std::unique_ptr<Thread>		processThread;

private:
	void tryConnectProcess();
	void receivePacketProcess();
	void run();

public:
	Terminal(Server *server, const std::wstring& name);
	~Terminal();
	
	void initialize(const std::string& ip, int port);
	void sendPacket(Packet *packet);

	std::wstring getName() const { return name.c_str(); }
	std::wstring getIP() const { return session.getIP(); }
	UInt16		 getPort() const { return session.getPort(); }

	TerminalStatus getStatus() const { return status; }
};
#endif