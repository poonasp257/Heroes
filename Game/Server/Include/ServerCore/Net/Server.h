#ifndef SERVER_H
#define SERVER_H

class ContentsProcess;

enum class ServerStatus {
	Stop,
	Initialize,
	Ready
};

class Server {
protected:
	std::array<char, SIZE_16> 	ip;
	int							port;
	int							workerThreadCount;

	ServerStatus				status;
	ContentsProcess 			*process;
	
public:
	Server(ContentsProcess *process);
	virtual ~Server();

	virtual bool run() = 0;

	ServerStatus getStatus() { return status; }

	void putPackage(Package *package);
};
#endif