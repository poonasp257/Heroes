#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

class SessionManager : public Singleton<SessionManager> {
public:
	const size_t 		MaxConnection;
	std::list<Session*> sessionList;

public:
	SessionManager();
	virtual ~SessionManager();

	bool AddSession(Session *session);
	bool CloseSession(Session *session);
	bool ForceCloseSession(Session *session);
};

#endif