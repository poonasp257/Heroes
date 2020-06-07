#ifndef WORLD_MANAGER_H
#define WORLD_MANAGER_H

#include "Sector.h"

class WorldManager {
private: 
	//QuadTree<Sector> worldNode;
	Sector sector;

private:
	WorldManager();
	~WorldManager();

public:
	WorldManager(const WorldManager&) = delete;
	WorldManager(WorldManager&&) = delete;
	WorldManager& operator=(const WorldManager&) = delete;
	WorldManager& operator=(WorldManager&&) = delete;

public:
	//Sector* findSector(objectId_t sessionId);
	Sector* findSector(const Vector3& position);

	static auto& Instance() {
		static WorldManager instance;
		return instance;
	}
};
#endif