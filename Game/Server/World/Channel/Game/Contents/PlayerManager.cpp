#include "stdafx.h"
#include "PlayerManager.h"

PlayerManager::PlayerManager() {

}

PlayerManager::~PlayerManager() {

}

void PlayerManager::registerPlayer(UInt64 newSessionId, const PlayerInfo& newCharacterInfo) {
	for (auto oldPlayer : playerTable) {
		if (oldPlayer.second.accountId != newCharacterInfo.accountId) continue;

		SessionManager::Instance().closeSession(oldPlayer.first);
	}

	playerTable.insert(std::make_pair(newSessionId, newCharacterInfo));
}

void PlayerManager::unregisterPlayer(UInt64 sessionId) {
	NotifyDisconnectPlayerPacket packet;
	packet.accountId = playerTable[sessionId].accountId;

	SessionManager::Instance().BroadcastPacket(&packet);
}

void PlayerManager::process() {
	while (true) {
		for (auto it = playerTable.begin(); it != playerTable.end();) {
			auto session = SessionManager::Instance().getSession(it->first);
			if (session) ++it;
			else {
				this->unregisterPlayer(it->first);
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