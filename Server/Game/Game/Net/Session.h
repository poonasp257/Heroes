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

	virtual void onSend(size_t transferSize) = 0;
	virtual void sendPacket(Packet *packet) = 0;

	virtual Package* onRecv(size_t tranferSize) = 0;
	virtual void recvStanBy() = 0;

	virtual bool onAccept(SOCKET socket, SOCKADDR_IN addrInfo);
	virtual void onClose();

	SOCKET& getSocket() { return sessionInfo.socket; }
	std::string getClientAddress();
};

#endif