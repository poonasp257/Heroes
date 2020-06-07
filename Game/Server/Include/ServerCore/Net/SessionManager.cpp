#include "stdafx.h"

SessionManager::SessionManager() : 
	MaxConnection(1000),
	lock(L"SessionManager") {

}

SessionManager::~SessionManager() {

}

bool SessionManager::addSession(std::shared_ptr<Session> session) {
	SAFE_LOCK(lock);
    if(MaxConnection <= sessionPool.size()) {
		WARNING_LOG(L"No connections are available");
        return false;
    }

	session->setId(this->generateId());
	sessionPool.insert(std::pair(session->getId(), std::move(session)));

	return true;
}

void SessionManager::closeSession(objectId_t sessionId) {
	SAFE_LOCK(lock);
	auto itr = sessionPool.find(sessionId);
	if (itr == sessionPool.end()) return;

	INFO_LOG(L"disconnected client...[%s]", itr->second->getIP().c_str());

	itr->second->onClose();
	sessionPool.erase(itr);
}

void SessionManager::closeSession(const Session* session) {
	SAFE_LOCK(lock);
	if (session == nullptr) return;

	auto itr = sessionPool.find(session->getId());
	if (itr == sessionPool.end()) return;

	INFO_LOG(L"disconnected client...[%s]", itr->second->getIP().c_str());

	itr->second->onClose();
	sessionPool.erase(itr);
}

void SessionManager::forceCloseSession(const Session* session) {
	SAFE_LOCK(lock);
	if (session == nullptr) return;

	auto itr = sessionPool.find(session->getId());
	if (itr == sessionPool.end()) return;

	INFO_LOG(L"disconnected client...[%s]", itr->second->getIP().c_str());

	LINGER linger = { 1, 0 };
	setsockopt(itr->second->getSocket(), SOL_SOCKET, SO_LINGER, (const char*)&linger, sizeof(linger));
	itr->second->onClose();
	sessionPool.erase(itr);
}

void SessionManager::BroadcastPacket(const Packet& packet, SessionType sessionType) {
	for (auto pair : sessionPool) {
		if (sessionType != pair.second->getType()) continue;

		pair.second->sendPacket(packet);
	}
}

Session* SessionManager::getSession(objectId_t sessionId) {
	SAFE_LOCK(lock);
	auto itr = sessionPool.find(sessionId);
	if (itr == sessionPool.end()) return nullptr;

	return itr->second.get();
}