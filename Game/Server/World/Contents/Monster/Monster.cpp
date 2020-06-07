#include "stdafx.h"
#include "Monster.h"
#include "MonsterZone.h"
#include "../Player/Player.h"

Monster::Monster(objectId_t typeId,
	MonsterZone& monsterZone,
	const Json::Value& monsterInfo,
	const Json::Value& transformInfo) :
	GameObject(),
	monsterZone(monsterZone),
	visualRange(30.0f),
	attackTimer(0.0f),
	spawnTimer(0.0f),
	AttackDelay(3.0f),
	targetPlayer(nullptr), 
	needReturnOriginPosition(false) {
	info.id = this->instanceId;
	info.typeId = typeId;
	info.name = ConvertAnsiToUnicode(monsterInfo["name"].GetString());
	info.level = monsterInfo["level"].GetInt();
	info.currentHp = monsterInfo["hp"].GetInt();
	info.maxHp = info.currentHp;
	info.damage = monsterInfo["damage"].GetUint();
	info.defense = monsterInfo["defense"].GetUint();

	Json::Document positionDocument, rotationDocument;
	positionDocument.Parse(transformInfo["position"].GetString());
	rotationDocument.Parse(transformInfo["rotation"].GetString());
	info.position.x = positionDocument["x"].GetFloat();
	info.position.y = positionDocument["y"].GetFloat();
	info.position.z = positionDocument["z"].GetFloat();
	info.rotation.x = rotationDocument["x"].GetFloat();
	info.rotation.y = rotationDocument["y"].GetFloat();
	info.rotation.z = rotationDocument["z"].GetFloat();
	info.originPosition = info.position;
	info.originRotation = info.rotation;

	visualRange.setCenter(info.position);
	originPosition = info.position;
	destination = info.position;

	respawnTime = monsterInfo["respawnTime"].GetFloat();
	name = Format(L"%s (%ull)", info.name.c_str(), instanceId);
}

Monster::~Monster() {

}

bool Monster::isInRange(objectId_t playerId) const {
	auto it = playersInRange.find(playerId);
	if (it == playersInRange.end()) return false;

	return  true;
}

void Monster::start() {

}

void Monster::update(float deltaTime) {
	if (!this->activeSelf) {
		spawnTimer += deltaTime;
		return;
	}

	attackTimer += deltaTime;

	if (needReturnOriginPosition) {
		if (info.position.distance(originPosition) > 1.0f) {
			this->moveto(originPosition, deltaTime);
			info.currentHp = info.maxHp;
			return;
		}

		needReturnOriginPosition = false;
		if (targetPlayer) this->removePlayerInRange(targetPlayer->getId());
	}

	if (monsterZone.isOutMoveBoundary(info.position)) {
		this->loseAggression();
		return;
	}

	if (!targetPlayer) {
		if (info.position.distance(originPosition) > 1.0f) {
			this->loseAggression();
		}

		targetPlayer = this->findTarget();
		return;
	}

	if (targetPlayer->isInvincibility()) return;
	
	const FloatVector& targetPos = targetPlayer->getPosition();
	float diffToPlayer = info.position.distance(targetPos);
	if (diffToPlayer <= 1.0f) {
		if (attackTimer > AttackDelay) {
			this->attack();
		}

		return;
	}

	float diffToDestination = info.position.distance(destination);
	//if(diffToPlayer <= diffToDestination) {
	//	destination = targetPos;
	//	diffToDestination = diffToPlayer;
	//	this->notifyMovement(destination);
	//}

	if (diffToDestination > 1.0f) {
		this->moveto(destination, deltaTime);
		return;
	}

	destination = targetPos;
	this->notifyMovement(destination);
}

void Monster::addPlayerInRange(const std::shared_ptr<Player>& player) {
	playersInRange[player->getId()] = player;
}

void Monster::removePlayerInRange(objectId_t playerId) {
	auto it = playersInRange.find(playerId);
	if (it == playersInRange.end()) return;

	playersInRange.erase(playerId);

	if (targetPlayer && targetPlayer->getId() == playerId) {
		this->loseAggression();
	}
}

void Monster::notifyPlayersInRange(const Packet& packet) {
	for (auto& pair : playersInRange) {
		Session* session = pair.second->getSession();
		session->sendPacket(packet);
	}
}

std::shared_ptr<Player> Monster::findTarget() {
	if (playersInRange.empty()) return nullptr;

	float minDistance = FLT_MAX;
	std::shared_ptr<Player> target = nullptr;
	for (auto& pair : playersInRange) {
		auto& player = pair.second;
		if (player->isDead()) continue;

		float distance = info.position.distance(player->getPosition());
		if (distance <= minDistance) {
			target = player;
			minDistance = distance;
		}
	}

	return target;
}

void Monster::die() {
	this->activeSelf = false;
	targetPlayer = nullptr;
	playersInRange.clear();
	destination = originPosition;

	attackTimer = 0;
	info.currentHp = 0;
}

void Monster::respawn() {
	spawnTimer = 0;
	this->activeSelf = true;
	info.currentHp = info.maxHp;
	info.position = info.originPosition;
	info.rotation = info.originRotation;
}

void Monster::takeDamage(UInt32 damage) {
	UInt32 attenuatedDamage = damage - info.defense;
	info.currentHp -= std::clamp(attenuatedDamage, (UInt32)1, damage);
	if (info.currentHp <= 0) this->die();
}

void Monster::attack() {
	attackTimer = 0;
	targetPlayer->takeDamage(info.damage);
	if (targetPlayer->isDead()) {
		NotifyMonsterActionPacket packet;
		packet.monsterId = this->instanceId;
		packet.zoneId = monsterZone.getId();
		packet.actionType = ActionType::Attack;
		this->notifyPlayersInRange(packet);
		this->loseAggression();
		return;
	}

	NotifyTakeDamagePlayerPacket packet;
	packet.zoneId = monsterZone.getId();
	packet.monsterId = this->instanceId;
	packet.monsterActionType = ActionType::Attack;
	packet.playerId = targetPlayer->getId();
	packet.playerHp = targetPlayer->getInfo().characterInfo.currentHp;
	monsterZone.notifyPlayersInRange(packet);
}

void Monster::moveto(const FloatVector& to, float deltaTime) {
	info.position = FloatVector::MoveTowards(info.position, to, deltaTime * 4.0f);
	visualRange.setCenter(info.position);
}

void Monster::loseAggression() {
	needReturnOriginPosition = true;
	targetPlayer = nullptr;

	NotifyLoseAggressionMonsterPacket packet;
	packet.zoneId = monsterZone.getId();
	packet.monsterId = this->instanceId;
	monsterZone.notifyPlayersInRange(packet);
}

void Monster::notifyMovement(const FloatVector& to) {
	NotifyMonsterMovementPacket packet;
	packet.zoneId = monsterZone.getId();
	packet.monsterId = this->instanceId;
	packet.movement.moveAmount = 1.0f;
	packet.movement.direction = (to - info.position).normalized();
	packet.movement.position = to;
	monsterZone.notifyPlayersInRange(packet);
}