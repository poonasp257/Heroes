#include "stdafx.h"

SessionManager::SessionManager() 
    : MaxConnection(1000) {

}

SessionManager::~SessionManager() {

}

bool SessionManager::addSession(Session *session) {
	std::lock_guard<std::mutex> guard(lock);

    auto found = std::find(sessionList.begin(), sessionList.end(), session);
    if(found != sessionList.end()) return false;
	
    if(MaxConnection <= sessionList.size()) {
        SystemLogger::Log(Logger::Info, "No connections are available");
        return false;
    }
    
    sessionList.push_back(session);
	return true;
}

bool SessionManager::closeSession(Session *session) {
	std::lock_guard<std::mutex> guard(lock);

    if(!session) return false;

    auto found = std::find(sessionList.begin(), sessionList.end(), session);
    if(found == sessionList.end()) return false;

    Session *delSession = *found;
    closesocket(delSession->getSocket());
    sessionList.erase(found);
    delete delSession;

	SystemLogger::Log(Logger::Info, "Close connection ");

    return true;
}

bool SessionManager::forceCloseSession(Session *session) {
	std::lock_guard<std::mutex> guard(lock);

    if(!session) return false;

    LINGER linger;
    linger.l_linger = 0;
    linger.l_onoff = 1;

    setsockopt(session->getSocket(), SOL_SOCKET, SO_LINGER, 
        (const char*)&linger, sizeof(linger));

    return this->closeSession(session);
}