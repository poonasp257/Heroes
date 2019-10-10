#ifndef SERVER_H
#define SERVER_H

enum class ServerStatus {
	Stop,
	Initialize,
	Ready
};

class Server
{
private:
	char			ip[16];
	int				port;
	int				workerThreadCount;

	ServerStatus	status;
public:
	Server();
	virtual ~Server();

	virtual void Initialize();
	virtual void Run() = 0;

	ServerStatus GetStatus() { return status; };
};

#endif