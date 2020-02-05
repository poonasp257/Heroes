#ifndef SESSION_H
#define SESSION_H

enum class SessionType {
	Client,
	Terminal
};

class Session {
protected:
	struct SessionInfo {
		SOCKET		socket;
		SOCKADDR_IN addrInfo;
	};

protected:
	SessionType type;
	SessionInfo sessionInfo;
	UInt64	id;

public:
	Session();
	virtual ~Session();

	virtual void onSend(size_t transferSize) = 0;
	virtual void sendPacket(Packet *packet) = 0;

	virtual Package* onRecv(size_t tranferSize) = 0;
	virtual void recvStandBy() = 0;

	virtual bool onAccept(SOCKET socket, SOCKADDR_IN addrInfo);
	virtual void onClose(bool isForced = false);

	SOCKET& getSocket() { return sessionInfo.socket; }
	UInt16 getPort() const { return ntohs(sessionInfo.addrInfo.sin_port); }
	std::wstring getIP() const;

	UInt64 getId() const { return id; }
	void setId(UInt64 id) { this->id = id; }

	SessionType getType() const { return type; }
	void setType(SessionType type) { this->type = type; }
};
#endif