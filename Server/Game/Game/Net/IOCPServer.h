#ifndef IOCPSERVER_H
#define IOCPSERVER_H

class IOCPServer : public Server, public Singleton<IOCPServer> {
public:
	IOCPServer();
	virtual ~IOCPServer();

	virtual bool Run();
};

#endif