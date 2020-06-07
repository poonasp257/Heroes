#include "stdafx.h"

SessionManager::SessionManager() 
	: MaxConnection(1000), lock(L"SessionManager") {

}

SessionManager::~SessionManager() {

}

bool SessionManager::addSession(std::shared_ptr<Session> session) {
	SAFE_LOCK(lock);

    auto itr = std::find(sessionList.begin(), sessionList.end(), session);
    if(itr != sessionList.end()) return false;
	
    if(MaxConnection <= sessionList.size()) {
		WARNING_LOG(L"No connections are available");
        return false;
    }

	session->setId(this->generateId());
    sessionList.push_back(std::move(session));

	return true;
}

void SessionManager::closeSession(objectId_t sessionId) {
	SAFE_LOCK(lock);

	auto itr = std::find_if(sessionList.begin(), sessionList.end(),
		[&sessionId](const auto& session) { return  session->getId() == sessionId; });
	if (itr == sessionList.end()) return;

	INFO_LOG(L"disconnected client...[%s]", (*itr)->getIP().c_str());

	(*itr)->onClose();
	sessionList.erase(itr);
}

void SessionManager::closeSession(const Session* session) {
	SAFE_LOCK(lock);

	if (session == nullptr) return;

	auto itr = std::find_if(sessionList.begin(), sessionList.end(),
		[&session](const auto& item) { return item.get() == session; });
	if (itr == sessionList.end()) return;

	INFO_LOG(L"disconnected client...[%s]", (*itr)->getIP().c_str());

	(*itr)->onClose();
	sessionList.erase(itr);
}

void SessionManager::forceCloseSession(const Session* session) {
	SAFE_LOCK(lock);

	if (session == nullptr) return;

	auto itr = std::find_if(sessionList.begin(), sessionList.end(),
		[&session](const auto& item) { return item.get() == session; });
	if (itr == sessionList.end()) return;

	INFO_LOG(L"disconnected client...[%s]", (*itr)->getIP().c_str());


	LINGER linger = { 1, 0 };
	setsockopt((*itr)->getSocket(), SOL_SOCKET, SO_LINGER, (const char*)&linger, sizeof(linger));
	(*itr)->onClose();
	sessionList.erase(itr);
}

void SessionManager::BroadcastPacket(const Packet& packet, SessionType sessionType) {
	for (auto session : sessionList) {
		if (sessionType != session->getType()) continue;

		session->sendPacket(packet);
	}
}

Session* SessionManager::getSession(objectId_t sessionId) {
	SAFE_LOCK(lock);
	
	for (auto session : sessionList) {
		if (session->getId() == sessionId) {
			return session.get();
		}
	}

	return nullptr;
}