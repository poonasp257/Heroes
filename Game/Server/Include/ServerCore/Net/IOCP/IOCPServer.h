#ifndef IOCPSERVER_H
#define IOCPSERVER_H

class ContentsProcess;

class IOCPServer : public Server {
private:
	HANDLE iocp;
	SOCKET listenSocket;
	std::vector<std::shared_ptr<Thread>> threadPool;

private:
	bool createListenSocket();

	void acceptThread();
	void workerThread();

public:
	IOCPServer(std::unique_ptr<ContentsProcess> process);
	~IOCPServer();

	virtual bool run();

	SOCKET	getListenSocket() { return listenSocket; }
	HANDLE	getIOCP() { return iocp; }
	void	onAccept(SOCKET accepter, SOCKADDR_IN addrInfo);
};
#endif