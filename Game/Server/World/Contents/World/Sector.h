#ifndef SECTOR_H
#define SECTOR_H

class Sector {
private:
	std::list<std::shared_ptr<Session>> sessionList;
	std::list<PlayerInfo> playerList;

public:
	Sector();
	~Sector();

	PlayerInfo* find(objectId_t sessionId);

	void broadcast(const Packet& packet);
	void broadcast(const Packet& packet, objectId_t excludingSessionId);

	void registerPlayer(std::shared_ptr<Session> newSession, const PlayerInfo& playerInfo);
	void unregisterPlayer(objectId_t sessionId);

	void updateMovement(objectId_t sessionId, CharacterMovement movement);

	std::list<PlayerInfo> getPlayerList() { return playerList; }
}; 
#endif