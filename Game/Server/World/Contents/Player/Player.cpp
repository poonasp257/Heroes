#include "stdafx.h"
#include "Player.h"
#include "PlayerManager.h"
#include "../Monster/MonsterZone.h"
#include "../Monster/MonsterManager.h"

Player::Player(Session* session, const std::wstring familyName, const CharacterInfo& info) :
 	GameObject(info.name),
    visualRange(45.0f), 
    invincibilityTimer(0.0f),
    InvincibilityTime(8.0f) {
    this->info.id = this->instanceId;
    this->info.familyName = familyName;
    this->info.characterInfo = info;
    this->session = session->shared_from_this();
    visualRange.setCenter(info.position);
    movement.moveAmount = 0.0f;
    movement.direction = { 0, 0, 0 };

    if (info.currentHp <= 0) {
        this->activeSelf = false;
    }
}

Player::~Player() {

}

void Player::start() {

}

void Player::update(float deltaTime) {
    if (isInvincibility()) invincibilityTimer += deltaTime;
}

bool Player::isInRange(objectId_t playerId) {
    auto it = playersInRange.find(playerId);
    if (it == playersInRange.end()) return false;

    return  true;
}

void Player::updateMovement(const CharacterMovement& movement) {
    info.characterInfo.position = movement.position;
    visualRange.setCenter(movement.position);
    this->movement = movement;
}

void Player::addPlayerInRange(std::shared_ptr<Player> otherPlayer) {
    playersInRange[otherPlayer->getId()] = otherPlayer;
    NotifyConnectPlayerPacket packet;
    packet.playerInfo = otherPlayer->getInfo();
    session->sendPacket(packet);
}

void Player::removePlayerInRange(std::shared_ptr<Player> otherPlayer) {
    objectId_t otherPlayerId = otherPlayer->getId();
    auto it = playersInRange.find(otherPlayerId);
    if (it == playersInRange.end()) return;

    playersInRange.erase(otherPlayerId);
    NotifyDisconnectPlayerPacket packet;
    packet.playerId = otherPlayerId;
    session->sendPacket(packet);
}

void Player::withinVisualRange(std::shared_ptr<Player> otherPlayer) {
    auto& playerTable = PlayerManager::Instance().getPlayerTable();
    otherPlayer->addPlayerInRange(playerTable[this->instanceId]);
    this->addPlayerInRange(otherPlayer);
}

void Player::outOfVisualRange(std::shared_ptr<Player> otherPlayer) {
    auto& playerTable = PlayerManager::Instance().getPlayerTable();
    otherPlayer->removePlayerInRange(playerTable[this->instanceId]);
    this->removePlayerInRange(otherPlayer);
}

void Player::notifyPlayersInRange(const Packet& packet) {
    for (auto& pair : playersInRange) {
        Session* session = pair.second->getSession();
        session->sendPacket(packet);
    }
}

void Player::notifyMovementInRange() {
    NotifyPlayerMovementPacket packet;
    packet.playerId = this->instanceId;
    packet.movement = this->movement;
    this->notifyPlayersInRange(packet);
}

void Player::notifyActionInRange(ActionType actionType) {
    NotifyPlayerActionPacket packet;
    packet.playerId = this->instanceId;
    packet.actionType = actionType;
    this->notifyPlayersInRange(packet);
}

void Player::levelUp() {
    auto& characterInfo = info.characterInfo;
    ++characterInfo.level;
    characterInfo.exp = 0;
    characterInfo.maxHp += 50;
    characterInfo.maxMp += 40;
    characterInfo.defense += 2;
    characterInfo.damage += 3;
    characterInfo.currentHp = characterInfo.maxHp;
    characterInfo.currentMp = characterInfo.maxMp;

    NotifyLevelUpPlayerPacket packet;
    packet.playerId = this->instanceId;
    packet.characterInfo = characterInfo;
    session->sendPacket(packet);
    this->notifyPlayersInRange(packet);
    return;
}

void Player::revive() {
    this->activeSelf = true;
    info.characterInfo.currentHp = info.characterInfo.maxHp;
    info.characterInfo.currentMp = info.characterInfo.maxMp;
    invincibilityTimer = 0;

    NotifyPlayerRevivePacket packet;
    packet.playerId = this->instanceId;
    this->notifyPlayersInRange(packet);
}

void Player::die() {
    this->activeSelf = false;
    info.characterInfo.currentHp = 0;

    NotifyPlayerDeadPacket packet;
    packet.playerId = this->instanceId;
    session->sendPacket(packet);
    this->notifyPlayersInRange(packet);
}

void Player::takeDamage(UInt32 damage) {
    UInt32 attenuatedDamage = damage - info.characterInfo.defense;
    info.characterInfo.currentHp -= std::clamp(attenuatedDamage, (UInt32)1, damage);;
    if (info.characterInfo.currentHp <= 0) this->die();
}

void Player::gainExp(float exp) {
    auto& characterInfo = info.characterInfo;
    characterInfo.exp += exp;
    float goalExp = 100 * characterInfo.level * characterInfo.level;
    if (characterInfo.exp >= goalExp) {
        this->levelUp();
        return;
    }

    GainMonsterExpPacket packet;
    packet.playerId = this->instanceId;
    packet.exp = characterInfo.exp;
    session->sendPacket(packet);
}