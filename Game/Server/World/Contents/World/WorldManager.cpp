#include "stdafx.h"
#include "Sector.h"
#include "WorldManager.h"
#include "../Monster/MonsterManager.h"
#include "../Player/PlayerManager.h"

WorldManager::WorldManager() :
	//sector(std::make_shared<Sector>()),
	updateProcess(nullptr),
 	playerManager(PlayerManager::Instance()),
	monsterManager(MonsterManager::Instance()) {

}

WorldManager::~WorldManager() {

}

void WorldManager::update() {
	Clock::Reset();
	while (true) {
		float deltaTime = Clock::DeltaTime();
		playerManager.update(deltaTime);
		monsterManager.update(deltaTime);
	}
}

Sector* WorldManager::findSector(const Vector3& position) {
	//auto sector = worldNode.find(FloatVector3(0, 0, 0));
	return nullptr; //this->sector.get();
}

bool WorldManager::initialize() {
	if (!MonsterManager::Instance().initialize()) {
		ERROR_LOG(L"Monster Manager initialized failed");
		return false;
	}

	if (!PlayerManager::Instance().initialize()) {
		ERROR_LOG(L"Player Manager initialized failed");
		return false;
	}

	JsonDocument document;
	bool result = ReadJsonFile(document, "world_map.json");
	if (!result) {
		ERROR_LOG(L"\"world_map\" could not be opened!");
		return false;
	}

	document["center"];
	document["height"];
	document["width"];

	return true;
}

bool WorldManager::run() {
	if (!MonsterManager::Instance().run()) {
		ERROR_LOG(L"Monster Manager couldn't start");
		return false;
	}

	if (!PlayerManager::Instance().run()) {
		ERROR_LOG(L"Player Manager couldn't start");
		return false;
	}

	updateProcess = MAKE_THREAD(WorldManager, update);
	if (updateProcess == nullptr) {
		ERROR_LOG(L"WorldManager couldn't start update process");
		return false;
	}

	return true;
}