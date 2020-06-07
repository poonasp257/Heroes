#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

class ConfigManager {
private:
	Json::Document config;

private:
	ConfigManager();
	~ConfigManager();

public:
	ConfigManager(const ConfigManager&) = delete;
	ConfigManager(ConfigManager&&) = delete;
	ConfigManager& operator=(const ConfigManager&) = delete;
	ConfigManager& operator=(ConfigManager&&) = delete;

	const Json::Document& getConfig() const { return config; }

	static auto& Instance() {
		static ConfigManager instance;
		return instance;
	}
};
#endif