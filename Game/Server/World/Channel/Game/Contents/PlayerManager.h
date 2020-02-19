#ifndef PLAYER_MANAGER_H
#define PALYER_MANAGER_H

class PlayerManager : public Singleton<PlayerManager> {
private:
	std::unordered_map<UInt64, PlayerInfo> playerTable;

	std::unique_ptr<Thread> thread;
	std::mutex lock;

private:
	void process();

public:
	PlayerManager();
	~PlayerManager();

	PlayerInfo* findBySessionId(UInt64 sessionId);
	PlayerInfo* findByAccountId(UInt64 accountId);

	void registerPlayer(UInt64 sessionId, const PlayerInfo& playerInfo);
	void unregisterPlayerBySessionId(UInt64 sessionId);
	void unregisterPlayerByAccountId(UInt64 accountId);
	   
	CharacterInfo* getCharacterInfo(UInt64 sessionId) { 
		return &playerTable[sessionId].characterInfo; 
	}

	std::unordered_map<UInt64, CharacterInfo> getPlayerTable();

	void run();
};
#endif