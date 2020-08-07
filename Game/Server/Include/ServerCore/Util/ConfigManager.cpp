#include "stdafx.h"

ConfigManager::ConfigManager() {
	bool result = ReadJsonFile(config, "config.json");
	if (!result) {
		ERROR_LOG(L"File could not be opened!");
		return;
	}
}

ConfigManager::~ConfigManager() {

}