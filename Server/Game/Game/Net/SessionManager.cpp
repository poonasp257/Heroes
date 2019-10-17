#include "stdafx.h"
#include "sessionManager.h"

SessionManager::SessionManager() 
    : MaxConnection(1000) {

}

SessionManager::~SessionManager() {

}

bool SessionManager::AddSession(Session *session) {
    auto found = std::find(sessionList.begin(), sessionList.end(), session);
    if(found != sessionList.end()) return false;
    if(MaxConnection <= sessionList.size()) {
        SystemLogger::Log("No connections are available");
        return false;
    }
    
    sessionList.push_back(session);
}

bool SessionManager::CloseSession(Session *session) {
    if(!session) return false;

    auto found = std::find(sessionList.begin(), sessionList.end(), session);
    if(found == sessionList.end()) return false;

    Session *delSession = *found;
    SystemLogger::Log("Close connection ");
    closesocket(delSession->GetSocket());
    sessionList.erase(found);
    delete delSession;

    return true;
}

bool SessionManager::ForceCloseSession(Session *session) {
    if(!session) return false;

    LINGER linger;
    linger.l_linger = 0;
    linger.l_onoff = 1;

    setsockopt(session->GetSocket(), SOL_SOCKET, SO_LINGER, 
        (const char*)&linger, sizeof(linger));

    return this->CloseSession(session);
}