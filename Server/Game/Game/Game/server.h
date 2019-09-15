#ifndef SERVER_H
#define SERVER_H

#include "pch.h"
//#include "SessionManager.h"

enum class ServerStatus {
	Initialize, Stop, Ready
};

class Server {
protected:
	char			ip[16];
	int				port;
	int				workerThreadCount;

	ServerStatus	status;
	//ContentsProcess	*contentsProcess;
public:
	//Server(ContentsProcess *contentsProcess);
	//virtual ~Server();

	//virtual void Initialize(xml_t)
};

#endif