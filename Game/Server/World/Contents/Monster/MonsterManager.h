#ifndef MONSTER_MANAGER_H
#define MONSTER_MANAGER_H

class MonsterZone;
class Player;

class MonsterManager {
private:
	using MonsterZoneTable = std::unordered_map<objectId_t, MonsterZone>;

private:
	MonsterZoneTable monsterZoneTable;

public:
	MonsterManager();
	~MonsterManager();

	MonsterManager(MonsterManager&&) = delete;
	MonsterManager(const MonsterManager&) = delete;
	MonsterManager& operator=(MonsterManager&&) = delete;
	MonsterManager& operator=(const MonsterManager&) = delete;

public:
	MonsterZoneTable& getMonsterZoneTable();
	MonsterZone* findMonsterZone(objectId_t zoneId);
	
	bool initialize();
	bool run();
	void update(float deltaTime);

	void updateVisualRange(const std::shared_ptr<Player>& player);

	static auto& Instance() {
		static MonsterManager instance;
		return instance;
	}
};

#endif