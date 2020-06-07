#include "stdafx.h"

ConfigManager::ConfigManager() {
	bool result = Json::ReadFile(config, "config.json");
	if (!result) {
		ERROR_LOG(L"File could not be opened!");
		return;
	}
}

ConfigManager::~ConfigManager() {

}