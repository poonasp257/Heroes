#include "stdafx.h"
#include "PlayerManager.h"
#include "Player.h"
#include "UserManager.h"
#include "../Monster/MonsterManager.h"
#include "../Monster/MonsterZone.h"

PlayerManager::PlayerManager() :
	lock(L"PlayerManager") {

}

PlayerManager::~PlayerManager() {

}

std::shared_ptr<Player> PlayerManager::find(const std::wstring& characterName) {
	SAFE_LOCK(lock);
	for (auto& pair : playerTable) {
		auto& player = pair.second;
		if (player->getName() != characterName)  continue;

		return player;
	}

	return nullptr;
}

std::shared_ptr<Player> PlayerManager::find(objectId_t playerId) {
	SAFE_LOCK(lock);
	auto itr = playerTable.find(playerId);
	if (itr == playerTable.end()) return nullptr;

	return itr->second;
}

bool PlayerManager::initialize() {
	bool result = ReadJsonFile(charactersData, "character_info.json");
	if (!result) {
		ERROR_LOG(L"\"character_info\" could not be opened!");
		return false;
	}

	return true;
}

bool PlayerManager::run() {
	return true;
}

void PlayerManager::update(float deltaTime) {
	SAFE_LOCK(lock);
	for (auto it = playerTable.begin(); it != playerTable.end(); ++it) {
		it->second->update(deltaTime);
	}
}

void PlayerManager::registerPlayer(Session* session, const std::wstring& familyName, const CharacterInfo& info) {
	SAFE_LOCK(lock);
	auto player = std::make_shared<Player>(session, familyName, info);
	objectId_t playerId = player->getId();
	playerTable.insert(std::make_pair(playerId, std::move(player)));
	this->updatePlayerVisualRange(playerId);

	ConnectChannelResponsePacket responsePacket;
	responsePacket.playerId = playerId;
	session->sendPacket(responsePacket);
	INFO_FILE_LOG(L"%s, enter game", playerTable[playerId]->getInfo().familyName.c_str());

	User* user = UserManager::Instance().find(session->getId());
	objectId_t accountId = user->accountId;
	session->addCloseEvent(L"unregisterPlayer",
		[accountId, playerId]() {
			std::shared_ptr<Player> player = PlayerManager::Instance().find(playerId);
			if (player == nullptr) return;

			PlayerInfo& info = player->getInfo();
			DBUpdateCharacterStatusRequestPacket packet;
			packet.accountId = accountId;
			packet.characterId = info.characterInfo.id;
			packet.level = info.characterInfo.level;
			packet.exp = info.characterInfo.exp;
			packet.hp = info.characterInfo.currentHp;
			packet.mp = info.characterInfo.currentMp;
			packet.position = info.characterInfo.position;
			packet.rotation = info.characterInfo.rotation;

			Terminal* terminal = TerminalManager::Instance().getTerminal(L"WorldDB");
			terminal->sendPacket(packet);
			PlayerManager::Instance().unregisterPlayer(playerId);
	});

	MonsterManager::Instance().updateVisualRange(playerTable[playerId]);	
}

void PlayerManager::unregisterPlayer(objectId_t playerId) {
	SAFE_LOCK(lock);
	auto itr = playerTable.find(playerId);
	if (itr == playerTable.end()) return;

	auto& unregisteredPlayer = itr->second;
	for (auto& pair : unregisteredPlayer->getPlayersInRange()) {
		pair.second->removePlayerInRange(unregisteredPlayer);
	}

	auto& monsterZoneTable = MonsterManager::Instance().getMonsterZoneTable();
	for (auto& pair : monsterZoneTable) {
		auto& monsterZone = pair.second;
		monsterZone.removePlayerInRange(playerId);
	}

	playerTable.erase(playerId);
}


void PlayerManager::updatePlayerVisualRange(objectId_t playerId) {
	auto& player = playerTable[playerId];
	auto& playerVisualRange = player->getVisualRange();
	for (auto& pair : playerTable) {
		auto& otherPlayer = pair.second;
		objectId_t otherPlayerId = otherPlayer->getId();
		if (otherPlayerId == playerId) continue;

		const Vector3& otherPos = otherPlayer->getPosition();
		if (!playerVisualRange.collide(otherPos)) {
			if (player->isInRange(otherPlayerId)) {
				SAFE_LOCK(lock);
				player->outOfVisualRange(otherPlayer);
			}

			continue;
		}

		if (player->isInRange(otherPlayerId)) continue;

		SAFE_LOCK(lock);
		player->withinVisualRange(otherPlayer);
	}
}