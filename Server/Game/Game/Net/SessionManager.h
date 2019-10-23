#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

class SessionManager : public Singleton<SessionManager> {
public:
	const size_t 		MaxConnection;
	std::list<Session*> sessionList;

public:
	SessionManager();
	virtual ~SessionManager();

	bool addSession(Session *session);
	bool closeSession(Session *session);
	bool forceCloseSession(Session *session);
};

#endif