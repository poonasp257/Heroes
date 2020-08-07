#ifndef MONSTER_H
#define MONSTER_H

class Player;
class MonsterZone;

class Monster : public GameObject {
private:
	using PlayerTable = std::unordered_map<objectId_t, std::shared_ptr<Player>>;

private:
	MonsterInfo info;
	BoundingCircle visualRange;
	MonsterZone& monsterZone;

	float attackTimer;
	float spawnTimer;
	float respawnTime;
	const float AttackDelay;
	std::shared_ptr<Player> targetPlayer;
	PlayerTable playersInRange;

	bool needReturnOriginPosition;
	FloatVector originPosition;
	FloatVector destination;

public:
	Monster(objectId_t typeId,
		MonsterZone& monsterZone,
		const JsonValue& monsterInfo, 
		const JsonValue& transformInfo);
	~Monster();

	virtual void start();
	virtual void update(float deltaTime);

	BoundingCircle& getVisualRange() { return visualRange; }
	MonsterInfo& getInfo() { return info; }
	bool canRespawn() const { return spawnTimer >= respawnTime; }
	bool isInRange(objectId_t playerId) const;
	bool isDead() const { return !this->activeSelf; }

	void addPlayerInRange(const std::shared_ptr<Player>& player);
	void removePlayerInRange(objectId_t playerId);
	void notifyPlayersInRange(const Packet& packet);
	std::shared_ptr<Player> findTarget();

	void die();
	void respawn();
	void takeDamage(UInt32 damage);
	void attack();
	void moveto(const FloatVector& to, float deltaTime);
	void loseAggression();

	void notifyMovement(const FloatVector& to);
};

#endif