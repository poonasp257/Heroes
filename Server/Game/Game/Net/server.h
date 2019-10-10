#ifndef SERVER_H
#define SERVER_H

enum class ServerStatus {
	Stop,
	Initialize,
	Ready
};

class Server
{
protected:
	char			ip[16];
	int				port;
	int				workerThreadCount;

	ServerStatus	status;
public:
	Server();
	virtual ~Server();

	virtual void Initialize(Json::Document& document);
	virtual bool Run() = 0;

	ServerStatus GetStatus() { return status; };
};

#endif