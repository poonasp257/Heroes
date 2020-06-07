#include "stdafx.h"
#include "Sector.h"

Sector::Sector() {

}

Sector::~Sector() {

}

PlayerInfo* Sector::find(objectId_t sessionId) {
	auto itr = std::find_if(playerList.begin(), playerList.end(),
		[&sessionId](const auto& pair) { return pair.first == sessionId; });
	if (itr == playerList.end()) return nullptr;

	return &itr->second;
}

void Sector::registerPlayer(objectId_t sessionId, const PlayerInfo& playerInfo) {
	playerList.push_back(std::make_pair(sessionId, playerInfo));

	/*NotifyConnectPlayerPacket packet;
	packet.playerInfo = playerInfo;
	SessionManager::Instance().BroadcastPacket(packet);*/
}

void Sector::unregisterPlayer(objectId_t sessionId) {
	auto itr = std::find_if(playerList.begin(), playerList.end(),
		[&sessionId](const auto& pair) { return pair.first == sessionId; });
	if (itr == playerList.end()) return;

	playerList.erase(itr);
	NotifyDisconnectPlayerPacket packet;
	packet.playerId = sessionId;
	SessionManager::Instance().BroadcastPacket(packet);
}