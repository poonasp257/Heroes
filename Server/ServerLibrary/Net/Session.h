#ifndef SESSION_H
#define SESSION_H

class Session {
protected:
	struct SessionInfo {
		SOCKET		socket;
		SOCKADDR_IN addrInfo;
	};

protected:
	SessionInfo sessionInfo;
	oid_t	id;

public:
	Session();
	virtual ~Session();

	virtual void onSend(size_t transferSize) = 0;
	virtual void sendPacket(Packet *packet) = 0;

	virtual Package* onRecv(size_t tranferSize) = 0;
	virtual void recvStandBy() = 0;

	virtual bool onAccept(SOCKET socket, SOCKADDR_IN addrInfo);
	virtual void onClose();

	SOCKET& getSocket() { return sessionInfo.socket; }
	std::string getClientAddress();

	oid_t getId() const { return id; }
	void	 setId(oid_t id) { this->id = id; }
};

#endif