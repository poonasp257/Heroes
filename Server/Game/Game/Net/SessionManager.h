#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

class SessionManager : public Singleton<SessionManager> {
public:
	SessionManager();
	~SessionManager();
};

#endif