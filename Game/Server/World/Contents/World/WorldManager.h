#ifndef WORLD_MANAGER_H
#define WORLD_MANAGER_H

class Sector;
class PlayerManager;
class MonsterManager;

class WorldManager {
private: 
	//QuadTree<Sector> worldNode;
	//std::shared_ptr<Sector> sector;
	std::shared_ptr<Thread> updateProcess;
	
	PlayerManager& playerManager;
	MonsterManager& monsterManager;

private:
	WorldManager();
	~WorldManager();

	WorldManager(WorldManager&&) = delete;
	WorldManager(const WorldManager&) = delete;
	WorldManager& operator=(WorldManager&&) = delete;
	WorldManager& operator=(const WorldManager&) = delete;

	void update();

public:
	Sector* findSector(const Vector3& position);

	bool initialize();
	bool run();

	static auto& Instance() {
		static WorldManager instance;
		return instance;
	}
};
#endif