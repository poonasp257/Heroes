#ifndef SESSION_H
#define SESSION_H

struct SessionInfo {
	SOCKET		socket;
	SOCKADDR_IN addrInfo;
};

class Session {
protected:
	SessionInfo sessionInfo;

public:
	Session();
	virtual ~Session();

	virtual bool Accept(SOCKET socket, SOCKADDR_IN addrInfo);

	virtual void Send(size_t transferSize) = 0;
	virtual void SendPacket(Packet *packet) = 0;

	virtual Package* Recv(size_t tranferSize) = 0;
	virtual void RecvStanBy() = 0;

	virtual void Close();

	SOCKET& GetSocket();
	std::string GetClientAddress();
};

#endif