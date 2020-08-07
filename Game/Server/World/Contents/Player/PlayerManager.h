#ifndef PLAYER_MANAGER_H
#define PLAYER_MANAGER_H

class Player;

class PlayerManager {
private:
	using PlayerTable = std::unordered_map<objectId_t, std::shared_ptr<Player>>;

private:
	CriticalSection lock;
	PlayerTable playerTable;

	JsonDocument charactersData;

private:
	PlayerManager();
	~PlayerManager();

	PlayerManager(PlayerManager&&) = delete;
	PlayerManager(const PlayerManager&) = delete;
	PlayerManager& operator=(PlayerManager&&) = delete;
	PlayerManager& operator=(const PlayerManager&) = delete;

public:
	CharacterInfo getCharacterData(CharacterClassType type, UInt32 level = 1) {
		const auto& characterData = charactersData[std::to_string((UInt16)type).c_str()];
		CharacterInfo characterInfo;
		characterInfo.maxHp = characterData["maxHp"].GetInt64() + level * 50;
		characterInfo.maxMp = characterData["maxMp"].GetInt64() + level * 40;
		characterInfo.defense = characterData["defense"].GetInt64() + level * 2;
		characterInfo.damage = characterData["damage"].GetUint64() + level * 3;
		return characterInfo;
	}

	PlayerTable& getPlayerTable() { 
		SAFE_LOCK(lock);
		return playerTable; 
	}

	bool initialize();
	bool run();
	void update(float deltaTime);

	std::shared_ptr<Player> find(const std::wstring& characterName);
	std::shared_ptr<Player> find(objectId_t playerId);

	void registerPlayer(Session* session, const std::wstring& familyName, const CharacterInfo& info);
	void unregisterPlayer(objectId_t playerId);

	void updatePlayerVisualRange(objectId_t playerId);

	static auto& Instance() {
		static PlayerManager instance;
		return instance;
	}
};
#endif