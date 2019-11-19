#ifndef IOCPSERVER_H
#define IOCPSERVER_H

class IOCPServer : public Server, public Singleton<IOCPServer> {
private:
	SOCKET listenSocket;
	HANDLE iocp;
	std::unique_ptr<Thread> acceptThread;
	std::array<std::unique_ptr<Thread>, SIZE_16> workerThreads;

private:
	bool createListenSocket();

	virtual bool initialize(Json::Document& document);
	
	static unsigned int WINAPI AcceptThread(LPVOID lpParam);
	static unsigned int WINAPI WorkerThread(LPVOID lpParam);

public:
	IOCPServer(ContentsProcess *process);
	virtual ~IOCPServer();

	virtual bool run();

	SOCKET	getListenSocket() { return listenSocket; }
	HANDLE	getIOCP() { return iocp; }
	void	onAccept(SOCKET accepter, SOCKADDR_IN addrInfo);
};

#endif