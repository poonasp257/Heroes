#ifndef SECTOR_H
#define SECTOR_H

class Sector {
private:
	std::list<std::pair<objectId_t, PlayerInfo>> playerList;

public:
	Sector();
	~Sector();

	PlayerInfo* find(objectId_t sessionId);

	void registerPlayer(objectId_t sessionId, const PlayerInfo& playerInfo);
	void unregisterPlayer(objectId_t sessionId);

	std::list<std::pair<objectId_t, PlayerInfo>> getPlayerList() { return playerList; }
}; 
#endif