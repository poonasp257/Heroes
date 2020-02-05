#include "stdafx.h"

SessionManager::SessionManager() 
    : MaxConnection(1000), sessionIdSeed(0) {

}

SessionManager::~SessionManager() {

}

bool SessionManager::addSession(Session *session) {
	std::lock_guard<std::mutex> guard(lock);

    auto found = std::find(sessionList.begin(), sessionList.end(), session);
    if(found != sessionList.end()) return false;
	
    if(MaxConnection <= sessionList.size()) {
        SystemLogger::Log(Logger::Info, L"No connections are available");
        return false;
    }

	session->setId(this->createSessionId());
    
    sessionList.push_back(session);
	return true;
}

bool SessionManager::closeSession(UInt64 sessionId) {
	Session *session = this->getSession(sessionId);
	return this->closeSession(session);
}

bool SessionManager::closeSession(Session *session) {
	std::lock_guard<std::mutex> guard(lock);

    if(!session) return false;

    auto found = std::find(sessionList.begin(), sessionList.end(), session);
    if(found == sessionList.end()) return false;
	
	SystemLogger::Log(Logger::Info, L"disconnected client...[%s]",
		session->getIP().c_str());

    Session *delSession = *found;
    closesocket(delSession->getSocket());
    sessionList.remove(delSession);
	if (delSession) delete delSession;

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

void SessionManager::BroadcastPacket(Packet *packet, SessionType sessionType) {
	for (auto session : sessionList) {
		if (sessionType != session->getType()) continue;

		session->sendPacket(packet);
	}
}

Session* SessionManager::getSession(UInt64 sessionId) {
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