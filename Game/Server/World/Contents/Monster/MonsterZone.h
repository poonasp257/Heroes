#ifndef MONSTER_ZONE_H
#define MONSTER_ZONE_H

class Monster;
class Player;

class MonsterZone : public GameObject {
private:
	using PlayerTable = std::unordered_map<objectId_t, std::shared_ptr<Player>>;

private:
	CriticalSection lock;
	BoundingCircle moveBoundary;
	BoundingCircle recognizeBoundary;
	std::unordered_map<objectId_t, Monster> monsterPool;

	PlayerTable playersInRange;

public:
	MonsterZone();
	MonsterZone(const Json::Value& zoneInfo);
	~MonsterZone();

	BoundingCircle& getMoveBoundary() { return moveBoundary; }
	BoundingCircle& getRecognizeBoundary() { return recognizeBoundary; }

	objectId_t getId() const { return instanceId; }
	MonsterZoneInfo getInfo();

	bool isInRange(objectId_t playerId);
	bool isOutMoveBoundary(const FloatVector& position) const {
		return !moveBoundary.collide(position);
	}
	bool isOutRecognizeBoundary(const FloatVector& position) const {
		return !recognizeBoundary.collide(position);
	}
		
	virtual void start();
	virtual void update(float deltaTime);

	void createNewMonster(Monster&& monster);
	void spawnMonster(objectId_t monsterId);
	void takeDamage(objectId_t monsterId, UInt64 playerId);
	
	void addPlayerInRange(const std::shared_ptr<Player>& player);
	void removePlayerInRange(objectId_t playerId);
	void updateVisualRange(const std::shared_ptr<Player>& player);
	void notifyPlayersInRange(const Packet& packet);
};

#endif