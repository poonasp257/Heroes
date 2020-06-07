#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

class Session;

class SessionManager {
private:
	const size_t 		MaxConnection;
	CriticalSection		lock;
	std::unordered_map<objectId_t, std::shared_ptr<Session>> sessionPool;

private:
	SessionManager();
	~SessionManager();

	SessionManager(SessionManager&&) = delete;
	SessionManager(const SessionManager&) = delete;
	SessionManager& operator=(SessionManager&&) = delete;
	SessionManager& operator=(const SessionManager&) = delete;

	objectId_t generateId() const {
		static objectId_t idSeed = 0;
		return ++idSeed;
	}

public:
	bool addSession(std::shared_ptr<Session> session);
	void closeSession(objectId_t sessionId);
	void closeSession(const Session* session);
	void forceCloseSession(const Session* session);

	void BroadcastPacket(const Packet& packet, SessionType sessionType = SessionType::Client);

	Session* getSession(objectId_t sessionId);
	size_t getConnectionCount() const { return sessionPool.size(); }

	static auto& Instance() {
		static SessionManager instance;
		return instance;
	}
};
#endif