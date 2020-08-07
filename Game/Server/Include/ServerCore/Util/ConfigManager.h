#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

class ConfigManager {
private:
	JsonDocument config;

private:
	ConfigManager();
	~ConfigManager();

	ConfigManager(ConfigManager&&) = delete;
	ConfigManager(const ConfigManager&) = delete;
	ConfigManager& operator=(ConfigManager&&) = delete;
	ConfigManager& operator=(const ConfigManager&) = delete;

public:
	const JsonDocument& getConfig() const { return config; }

	static auto& Instance() {
		static ConfigManager instance;
		return instance;
	}
};
#endif