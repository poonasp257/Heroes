#include "stdafx.h"
#include "Monster.h"
#include "MonsterZone.h"
#include "MonsterManager.h"
#include "../Player/Player.h"

MonsterManager::MonsterManager() {

}

MonsterManager::~MonsterManager() {

}

MonsterManager::MonsterZoneTable& MonsterManager::getMonsterZoneTable() {
	return monsterZoneTable;
}

MonsterZone* MonsterManager::findMonsterZone(objectId_t zoneId) {
	auto it = monsterZoneTable.find(zoneId);
	if (it == monsterZoneTable.end()) return nullptr;

	return &it->second;
}

bool MonsterManager::initialize() {
	Json::Document zoneData;
	bool result = Json::ReadFile(zoneData, "monster_zone_info.json");
	if (!result) {
		ERROR_LOG(L"\"monster_zone_info\" could not be opened!");
		return false;
	}

	Json::Document monsterData;
	result = Json::ReadFile(monsterData, "monster_info.json");
	if (!result) {
		ERROR_LOG(L"\"monster_info\" could not be opened!");
		return false;
	}

	auto rootArray = zoneData["monsterZones"].GetArray();
	for (const auto& zoneProperty : rootArray) {
		MonsterZone monsterZone(zoneProperty);
		objectId_t zoneId = monsterZone.getId();
		monsterZoneTable.insert(std::make_pair(zoneId, std::move(monsterZone)));

		auto& spawnZone = monsterZoneTable[zoneId];
		for (auto& monsterProperty : zoneProperty["monsters"].GetArray()) {
			objectId_t typeId = monsterProperty["typeId"].GetUint64();
			const auto& monsterInfo = monsterData[std::to_string(typeId).c_str()];
			Monster monster(typeId, spawnZone, monsterInfo, monsterProperty);
			monster.start();
			spawnZone.createNewMonster(std::move(monster));
		}
	}

	return true;
}

bool MonsterManager::run() {
	for (auto& pair : monsterZoneTable) {
		pair.second.start();
	}
	
	return true;
}

void MonsterManager::update(float deltaTime) {
	for (auto& pair : monsterZoneTable) {
		auto& monsterZone = pair.second;
		pair.second.update(deltaTime);
	}
}

void MonsterManager::updateVisualRange(const std::shared_ptr<Player>& player) {
	const FloatVector& playerPosition = player->getPosition();
	objectId_t playerId = player->getId();
	for (auto& pair : monsterZoneTable) {
		auto& monsterZone = pair.second;
		if (pair.second.isOutRecognizeBoundary(playerPosition)) {
			if (monsterZone.isInRange(playerId)) {
				monsterZone.removePlayerInRange(playerId);
			}

			continue;
		}

		if (!monsterZone.isInRange(playerId)) {
			monsterZone.addPlayerInRange(player);
		}

		monsterZone.updateVisualRange(player);
	}
}