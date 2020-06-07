#include "stdafx.h"
#include "WorldManager.h"

WorldManager::WorldManager() {

}

WorldManager::~WorldManager() {

}

Sector* WorldManager::findSector(const Vector3& position) {
	//return worldNode.find(position);
	return &sector;
}