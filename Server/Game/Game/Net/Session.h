#ifndef SESSION_H
#define SESSION_H

struct SessionInfo {
	SOCKET		socket;
	SOCKADDR_IN addrInfo;
};

class Packet;
class Package;

class Session {
protected:
	SessionInfo sessionInfo;

public:
	Session();
	virtual ~Session();

	virtual void Accept(SOCKET socket, SOCKADDR_IN addrInfo);

	virtual void OnSend(size_t transferSize) = 0;
	virtual void SendPacket(Packet *packet) = 0;

	virtual Package* OnRecv(size_t tranferSize) = 0;
	virtual void RecvStanBy() = 0;

	virtual void Close();

	SOCKET& GetSocket() { return sessionInfo.socket; }
	char* GetClientAddress();
};

#endif