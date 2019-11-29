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

	session->setId(sessionList.size());
    
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
    sessionList.remove(delSession);
	if (delSession) delete delSession;

	SystemLogger::Log(Logger::Info, "disconnected client...[%s]",
		session->getClientAddress().c_str());

    return true;
}

void SessionManager::forceCloseSession(Session *session) {
	std::lock_guard<std::mutex> guard(lock);

    if(!session) return;

    LINGER linger;
    linger.l_linger = 0;
    linger.l_onoff = 1;

    setsockopt(session->getSocket(), SOL_SOCKET, SO_LINGER, 
        (const char*)&linger, sizeof(linger));

	this->closeSession(session);
}

void SessionManager::BroadcastPacket(Packet *packet) {
	for (auto session : sessionList) {
		session->sendPacket(packet);
	}
}

Session* SessionManager::getSession(oid_t sessionId) {
	std::lock_guard<std::mutex> guard(lock);
	Session *findSession = nullptr;

	for (auto session : sessionList) {
		if (session->getId() == sessionId) {
			findSession = session;
			break;
		}
	}

	return findSession;
}