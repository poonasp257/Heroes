#ifndef SERVER_H
#define SERVER_H

class ContentsProcess;
class Package;

enum class ServerState {
	Stop,
	Running
};

class Server : public std::enable_shared_from_this<Server> {
protected:
	std::wstring						name;
	std::array<char, SIZE_16> 			ip;
	int									port;
	int									workerThreadCount;

	std::unique_ptr<ContentsProcess>	contentsProcess;

	static ServerState					state;

public:
	Server(std::unique_ptr<ContentsProcess> process);
	virtual ~Server();

	virtual bool run() = 0;

	const wchar_t* getName() const { return name.c_str(); }

	void putPackage(std::unique_ptr<Package>& package);

	static void setState(ServerState state) { Server::state = state; }
	static ServerState getState() { return state; }
};
#endif