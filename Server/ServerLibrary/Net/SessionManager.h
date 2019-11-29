#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

class SessionManager : public Singleton<SessionManager> {
private:
	const size_t 		MaxConnection;
	std::list<Session*> sessionList;
	std::mutex			lock;

public:
	SessionManager();
	virtual ~SessionManager();

	bool addSession(Session *session);
	bool closeSession(Session *session);
	void forceCloseSession(Session *session);

	void BroadcastPacket(Packet *packet);

	Session* getSession(oid_t sessionId);
	size_t getConnectionCount() const { return sessionList.size(); }
};
#endif