#include "stdafx.h"
#include "Monster.h"
#include "MonsterZone.h"
#include "../Player/Player.h"
#include "../Player/PlayerManager.h"

MonsterZone::MonsterZone() :
	GameObject(), 
	lock(L"MonsterZone") {


}

MonsterZone::MonsterZone(const JsonValue& zoneInfo) :
	GameObject(),
	lock(L"MonsterZone"),
	moveBoundary(35.0f),
	recognizeBoundary(80.0f) {
	JsonDocument positionDocument;
	positionDocument.Parse(zoneInfo["position"].GetString());
	moveBoundary.setCenter(
		positionDocument["x"].GetFloat(),
		positionDocument["y"].GetFloat(),
		positionDocument["z"].GetFloat());
	recognizeBoundary.setCenter(moveBoundary.getCenter());
}

MonsterZone::~MonsterZone() {

}

MonsterZoneInfo MonsterZone::getInfo() {
	MonsterZoneInfo zoneInfo;
	zoneInfo.id = this->instanceId;
	zoneInfo.position = recognizeBoundary.getCenter();
	for (auto& pair : monsterPool) {
		auto& monster = pair.second;
		zoneInfo.monsterList.push_back(monster.getInfo());
	}

	return zoneInfo;
}

void MonsterZone::createNewMonster(Monster&& monster) {
	monsterPool.insert(std::make_pair(monster.getId(), std::move(monster)));
}

void MonsterZone::spawnMonster(objectId_t monsterId) {
	auto it = monsterPool.find(monsterId);
	if (it == monsterPool.end()) return;
	
	Monster& monster = it->second;
	monster.respawn();

	NotifyRespawnMonsterPacket packet;
	packet.zoneId = this->instanceId;
	packet.monsterId = monsterId;
	this->notifyPlayersInRange(packet);
}

void MonsterZone::takeDamage(objectId_t monsterId, UInt64 playerId) {
	auto it = monsterPool.find(monsterId);
	if (it == monsterPool.end()) return;

	SAFE_LOCK(lock);
	Monster& monster = it->second;
	if (monster.isDead()) return;

	std::shared_ptr<Player> player = PlayerManager::Instance().find(playerId);
	if (player->isInvincibility()) return;

	auto& playerInfo = player->getInfo().characterInfo;
	monster.takeDamage(playerInfo.damage);

	NotifyTakeDamageMonsterPacket packet;
	packet.zoneId = this->instanceId;
	packet.monsterId = monster.getId();
	packet.hp = monster.getInfo().currentHp;
	this->notifyPlayersInRange(packet);

	if (monster.isDead()) {
		float exp = (monster.getInfo().level - playerInfo.level + 10) * 10;
		player->gainExp(exp);
	}
}

void MonsterZone::start() {
	for (auto& pair : monsterPool) {
		auto& monster = pair.second;
		monster.start();
	}
}

void MonsterZone::update(float deltaTime) {
	for (auto& pair : monsterPool) {
		SAFE_LOCK(lock);
		auto& monster = pair.second;
		if (!monster.isEnabled() && monster.canRespawn()) {
			this->spawnMonster(pair.first);
		}

		monster.update(deltaTime);
	}
}

bool MonsterZone::isInRange(objectId_t playerId) {
	SAFE_LOCK(lock);
	auto it = playersInRange.find(playerId);
	if (it == playersInRange.end()) return false;

	return  true;
}

void MonsterZone::addPlayerInRange(const std::shared_ptr<Player>& player) {
	GetMonsterListPacket packet;
	packet.monsterZone = this->getInfo();
	Session* session = player->getSession();
	session->sendPacket(packet);

	SAFE_LOCK(lock);
	playersInRange[player->getId()] = player;
}

void MonsterZone::removePlayerInRange(objectId_t playerId) {
	SAFE_LOCK(lock);
	auto it = playersInRange.find(playerId);
	if (it == playersInRange.end()) return;

	for (auto& pair : monsterPool) {
		auto& monster = pair.second;
		if (!monster.isInRange(playerId)) continue;

		monster.removePlayerInRange(playerId);
	}

	playersInRange.erase(playerId);
}

void MonsterZone::updateVisualRange(const std::shared_ptr<Player>& player) {
	const FloatVector& playerPosition = player->getPosition();
	objectId_t playerId = player->getId();
	for (auto& pair : monsterPool) {
		SAFE_LOCK(lock);
		auto& monster = pair.second;
		if (!monster.isEnabled()) continue;

		if (isOutMoveBoundary(playerPosition)) {
			if (!player->isInvincibility() && monster.isInRange(playerId)) {
				monster.removePlayerInRange(playerId);
			}

			continue;
		}

		auto& visualRange = monster.getVisualRange();
		if (monster.isInRange(playerId) ||
			!visualRange.collide(playerPosition)) continue;
		
		monster.addPlayerInRange(player);
	}
}

void MonsterZone::notifyPlayersInRange(const Packet& packet) {
	for (auto& pair : playersInRange) {
		Session* session = pair.second->getSession();
		session->sendPacket(packet);
	}
}