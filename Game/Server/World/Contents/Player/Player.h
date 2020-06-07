#ifndef PLAYER_H
#define PLAYER_H

class Player : public GameObject {
private:
	using PlayerTable = std::unordered_map<objectId_t, std::shared_ptr<Player>>;

private:
	PlayerInfo info;
	CharacterMovement movement;

	BoundingCircle visualRange;
	PlayerTable playersInRange;

	std::shared_ptr<Session> session;

	float invincibilityTimer;
	const float InvincibilityTime;

public:
	Player(Session* session, const std::wstring familyName, const CharacterInfo& info);
	~Player();

	BoundingCircle& getVisualRange() { return visualRange; }

	virtual void start();
	virtual void update(float deltaTime);

	bool isInRange(objectId_t playerId);
	bool isInvincibility() const { return invincibilityTimer < InvincibilityTime; }
	bool isDead() const { return !this->activeSelf; }

	PlayerInfo& getInfo() { return info; }
	Vector3& getPosition() { return info.characterInfo.position; }
	Session* getSession() { return session.get(); }
	PlayerTable& getPlayersInRange() { return playersInRange; }

	void updateMovement(const CharacterMovement& movement);

	void addPlayerInRange(std::shared_ptr<Player> player);
	void removePlayerInRange(std::shared_ptr<Player> player);
	void withinVisualRange(std::shared_ptr<Player> otherPlayer);
	void outOfVisualRange(std::shared_ptr<Player> otherPlayer);

	void notifyPlayersInRange(const Packet& packet);
	void notifyMovementInRange();
	void notifyActionInRange(ActionType actionType);

	void levelUp();
	void revive();
	void die();
	void takeDamage(UInt32 damage);
	void gainExp(float exp);
};
#endif