#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

class SessionManager : public Singleton<SessionManager> {
private:
	const size_t 		MaxConnection;
	UInt64				sessionIdSeed;
	std::list<Session*> sessionList;
	std::mutex			lock;

public:
	SessionManager();
	virtual ~SessionManager();

	bool addSession(Session *session);
	bool closeSession(Session *session);
	void forceCloseSession(Session *session);

	void BroadcastPacket(Packet *packet, SessionType sessionType = SessionType::Client);

	Session* getSession(UInt64 sessionId);
	size_t getConnectionCount() const { return sessionList.size(); }

	UInt64 createSessionId() { return ++sessionIdSeed; }
};
#endif