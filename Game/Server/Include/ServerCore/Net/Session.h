#ifndef SESSION_H
#define SESSION_H

class Package;

enum class SessionType {
	Client,
	Terminal
};

class Session : public std::enable_shared_from_this<Session> {
private:
	std::vector<std::pair<std::wstring, std::function<void()>>> closeEventList;

protected:
	struct SessionInfo {
		SOCKET		socket;
		SOCKADDR_IN addrInfo;
	};

protected:
	SessionType type;
	SessionInfo sessionInfo;
	objectId_t	id;

public:
	Session();
	virtual ~Session();

	virtual void onSend(size_t transferSize) = 0;
	virtual void sendPacket(const Packet& packet) = 0;

	virtual std::unique_ptr<Package> onRecv(size_t tranferSize) = 0;
	virtual void recvStandBy() = 0;

	virtual void onAccept(SOCKET socket, SOCKADDR_IN addrInfo);

	std::shared_ptr<Session> getPtr() { return shared_from_this(); }

	SOCKET getSocket() const { return sessionInfo.socket; }
	UInt16 getPort() const { return ntohs(sessionInfo.addrInfo.sin_port); }
	std::wstring getIP() const;

	objectId_t getId() const { return id; }
	void setId(objectId_t id) { this->id = id; }

	SessionType getType() const { return type; }
	void setType(SessionType type) { this->type = type; }

	void onClose();
	void addCloseEvent(const std::wstring& name, std::function<void()> closeEvent);
	void removeCloseEvent(const std::wstring& name);
};
#endif