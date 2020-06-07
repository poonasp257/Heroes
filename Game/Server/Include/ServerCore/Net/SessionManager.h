#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

class Session;

class SessionManager {
private:
	const size_t 		MaxConnection;
	CriticalSection		lock;
	std::list<std::shared_ptr<Session>> sessionList;

private:
	SessionManager();
	~SessionManager();

	objectId_t generateId() const {
		static objectId_t idSeed = 0;
		return ++idSeed;
	}

public:
	SessionManager(const SessionManager&) = delete;
	SessionManager(SessionManager&&) = delete;
	SessionManager& operator=(const SessionManager&) = delete;
	SessionManager& operator=(SessionManager&&) = delete;

	bool addSession(std::shared_ptr<Session> session);
	void closeSession(objectId_t sessionId);
	void closeSession(const Session* session);
	void forceCloseSession(const Session* session);

	void BroadcastPacket(const Packet& packet, SessionType sessionType = SessionType::Client);

	Session* getSession(objectId_t sessionId);
	size_t getConnectionCount() const { return sessionList.size(); }

	static auto& Instance() {
		static SessionManager instance;
		return instance;
	}
};
#endif