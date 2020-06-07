#include "stdafx.h"
#include "Sector.h"

Sector::Sector() {

}

Sector::~Sector() {

}

void Sector::broadcast(const Packet& packet) {
	for (auto& session : sessionList) {
		session->sendPacket(packet);
	}
}

void Sector::broadcast(const Packet& packet, objectId_t excludingSessionId) {
	for (auto& session : sessionList) {
		if (session->getId() == excludingSessionId) continue;

		session->sendPacket(packet);
	}
}

PlayerInfo* Sector::find(objectId_t sessionId) {
	auto itr = std::find_if(playerList.begin(), playerList.end(),
		[&sessionId](const auto& player) { return player.id == sessionId; });
	if (itr == playerList.end()) return nullptr;

	return &(*itr);
}

void Sector::registerPlayer(std::shared_ptr<Session> newSession, const PlayerInfo& playerInfo) {
	NotifyConnectPlayerPacket packet;
	packet.playerInfo = playerInfo;
	this->broadcast(packet);

	sessionList.push_back(std::move(newSession));
	playerList.push_back(playerInfo);
}

void Sector::unregisterPlayer(objectId_t sessionId) {
	auto foundSession = std::find_if(sessionList.begin(), sessionList.end(),
		[&sessionId](const auto& session) { return session->getId() == sessionId; });
	if (foundSession == sessionList.end()) return;

	sessionList.erase(foundSession);

	auto foundPlayer = std::find_if(playerList.begin(), playerList.end(),
		[&sessionId](const auto& player) { return player.id == sessionId; });
	if (foundPlayer == playerList.end()) return;

	playerList.erase(foundPlayer);

	NotifyDisconnectPlayerPacket packet;
	packet.playerId = sessionId;
	this->broadcast(packet);
}

void Sector::updateMovement(objectId_t sessionId, CharacterMovement movement) {
	NotifyPlayerMovementStayPacket packet;
	packet.playerId = sessionId;
	packet.movement = movement;
	this->broadcast(packet, sessionId);
}