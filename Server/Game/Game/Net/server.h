#ifndef SERVER_H
#define SERVER_H

enum class ServerStatus {
	Stop,
	Initialize,
	Ready
};

class Json;
class FileLogger;

class Server {
protected:
	std::array<char, SIZE_16> 	ip;
	int							port;
	int							workerThreadCount;

	Json						json;
	FileLogger					logger;
	ServerStatus				status;
	
public:
	Server(const char *logFileName);
	virtual ~Server();

	virtual bool Initialize(Json::Document& document) = 0;
	virtual bool Run() = 0;

	ServerStatus status() { return status; };
};

#endif