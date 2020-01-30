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
	void connectProcess();
	void run();

public:
	Terminal(Server *server, const std::wstring& name);
	~Terminal();
	
	void initialize(const std::string& ip, int port);
	void sendPacket(Packet *packet);

	const wchar_t* getName() const { return name.c_str(); }
	const char* getIP() const { return ip.data(); }
	UInt16		 getPort() const { return port; }

	TerminalStatus getStatus() const { return status; }
};
#endif