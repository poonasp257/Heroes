#ifndef PLAYER_MANAGER_H
#define PALYER_MANAGER_H

struct PlayerInfo {
	UInt64 accountId;
	CharacterInfo characterInfo;
};

class PlayerManager : public Singleton<PlayerManager> {
private:
	std::unordered_map<UInt64, PlayerInfo> playerTable; // sessionId, Player info...

	std::unique_ptr<Thread> thread;
	std::mutex lock;

private:
	void process();

public:
	PlayerManager();
	~PlayerManager();

	void registerPlayer(UInt64 newSessionId, const PlayerInfo& newCharacterInfo);
	void unregisterPlayer(UInt64 sessionId);

	CharacterInfo* getCharacterInfo(UInt64 sessionId) { 
		return &playerTable[sessionId].characterInfo; 
	}

	std::unordered_map<UInt64, CharacterInfo> getPlayerTable();

	void run();
};
#endif