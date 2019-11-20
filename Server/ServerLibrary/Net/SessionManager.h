#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

class SessionManager : public Singleton<SessionManager> {
private:
	const size_t 		MaxConnection;
	std::list<Session*> sessionList;

public:
	SessionManager();
	virtual ~SessionManager();

	bool addSession(Session *session);
	bool closeSession(Session *session);
	bool forceCloseSession(Session *session);

	size_t getConnectionCount() const { return sessionList.size(); }
};
#endif