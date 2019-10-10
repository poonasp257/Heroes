#ifndef IOCPSERVER_H
#define IOCPSERVER_H

class IOCPServer : public Server, public Singleton<IOCPServer> {
private:
	SOCKET listenSocket;
	HANDLE iocp;

private:
	bool CreateListenSocket();

	static unsigned int WINAPI AcceptThread(LPVOID lpParam);
	static unsigned int WINAPI WorkerThread(LPVOID lpParam);

public:
	IOCPServer();
	virtual ~IOCPServer();

	virtual bool Run();

	SOCKET	GetListenSocket() { return listenSocket; }
	HANDLE	GetHandleIOCP() { return iocp; }
	void	OnAccept(SOCKET accepter, SOCKADDR_IN addrInfo);
};

#endif