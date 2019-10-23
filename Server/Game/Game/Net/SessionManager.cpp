#include "stdafx.h"
#include "sessionManager.h"

SessionManager::SessionManager() 
    : MaxConnection(1000) {

}

SessionManager::~SessionManager() {

}

bool SessionManager::addSession(Session *session) {
    auto found = std::find(sessionList.begin(), sessionList.end(), session);
    if(found != sessionList.end()) return false;
    if(MaxConnection <= sessionList.getSize()) {
        SystemLogger::Log(Logger::Info, "No connections are available");
        return false;
    }
    
    sessionList.push_back(session);
}

bool SessionManager::closeSession(Session *session) {
    if(!session) return false;

    auto found = std::find(sessionList.begin(), sessionList.end(), session);
    if(found == sessionList.end()) return false;

    Session *delSession = *found;
    SystemLogger::Log(Logger::Info, "Close connection ");
    closesocket(delSession->getSocket());
    sessionList.erase(found);
    delete delSession;

    return true;
}

bool SessionManager::forceCloseSession(Session *session) {
    if(!session) return false;

    LINGER linger;
    linger.l_linger = 0;
    linger.l_onoff = 1;

    setsockopt(session->getSocket(), SOL_SOCKET, SO_LINGER, 
        (const char*)&linger, sizeof(linger));

    return this->closeSession(session);
}