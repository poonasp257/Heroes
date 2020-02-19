#include "stdafx.h"
#include "PlayerManager.h"

PlayerManager::PlayerManager() {

}

PlayerManager::~PlayerManager() {

}

PlayerInfo* PlayerManager::findBySessionId(UInt64 sessionId) {
	auto itr = playerTable.find(sessionId);
	if (itr == playerTable.end()) return nullptr;

	return &itr->second;
}

PlayerInfo* PlayerManager::findByAccountId(UInt64 accountId) {
	/*auto itr = std::find_if(playerTable.begin(), playerTable.end(),
		[&]( player) -> bool { return player.accountId == accountId; });
	if (itr == playerTable.end()) */
		return nullptr;

	//return &itr->second;
}

void PlayerManager::registerPlayer(UInt64 sessionId, const PlayerInfo& playerInfo) {
	playerTable.insert(std::make_pair(sessionId, playerInfo));
}

void PlayerManager::unregisterPlayerBySessionId(UInt64 sessionId) {
//	auto itr = playerTable.find

}

void PlayerManager::unregisterPlayerByAccountId(UInt64 accountId) {
	
}
//
//NotifyDisconnectPlayerPacket packet;
//packet.accountId = playerTable[sessionId].accountId;
//
//SessionManager::Instance().BroadcastPacket(&packet);

void PlayerManager::process() {
	while (true) {
		for (auto it = playerTable.begin(); it != playerTable.end();) {
			auto session = SessionManager::Instance().getSession(it->first);
			if (session) ++it;
			else {
				//this->unregisterPlayer(it->first);
				it = playerTable.erase(it);
			}
		}

		Sleep(100);
	}
}

void PlayerManager::run() {
	thread = std::make_unique<Thread>(new std::thread(&PlayerManager::process, this));
}

std::unordered_map<UInt64, CharacterInfo> PlayerManager::getPlayerTable() {
	std::unordered_map<UInt64, CharacterInfo> clientPlayerTable;

	for (auto player : playerTable) {
		const PlayerInfo &playerInfo = player.second;
		clientPlayerTable.insert(std::make_pair(playerInfo.accountId, playerInfo.characterInfo));
	}

	return clientPlayerTable;
}