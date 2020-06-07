#include "stdafx.h"

DBManager::DBManager() : 
	port(0), 
	workerCount(0) {
	
}

DBManager::~DBManager() {
    for (auto& db : dbPool) {
		if (!db) continue;

		db->setState(DBState::Stop);
        db->disconnect();
    }
}

void DBManager::pushQuery(std::unique_ptr<Query> query) {
    queryPool->push(query);
}

void DBManager::popQuery(std::unique_ptr<Query>& query) {
	queryPool->pop(query);
}

bool DBManager::initialize() {
	const auto& config = ConfigManager::Instance().getConfig();
	const Json::Value& dbConfig = config["Database"];
	if (dbConfig.IsNull()) {
		ERROR_LOG(L"\'Database\' document doesn't exist");
		return false;
	}

	if (dbConfig["IP"].IsNull()) {
		ERROR_LOG(L"\'Database:IP\' document doesn't exist");
		return false;
	}
	else if (dbConfig["Port"].IsNull()) {
		ERROR_LOG(L"\'Database:Port\' document doesn't exist");
		return false;
	}
	else if (dbConfig["DBName"].IsNull()) {
		ERROR_LOG(L"\'Database:DBName\' document doesn't exist");
		return false;
	}
	else if (dbConfig["ID"].IsNull()) {
		ERROR_LOG(L"\'Database:Id\' document doesn't exist");
		return false;
	}
	else if (dbConfig["Password"].IsNull()) {
		ERROR_LOG(L"\'Database:Password\' document doesn't exist");
		return false;
	}
	else if (dbConfig["ThreadCount"].IsNull()) {
		ERROR_LOG(L"\'Database:ThreadCount\' document doesn't exist");
		return false;
	}

	ip = ConvertAnsiToUnicode(dbConfig["IP"].GetString());
	port = dbConfig["Port"].GetInt();
	dbName = ConvertAnsiToUnicode(dbConfig["DBName"].GetString());
	id = ConvertAnsiToUnicode(dbConfig["ID"].GetString());
	password = ConvertAnsiToUnicode(dbConfig["Password"].GetString());
	workerCount = dbConfig["ThreadCount"].GetInt();

	for (int i = 0; i < workerCount; ++i) {
		dbPool.push_back(std::make_unique<ODBCDatabase>());
	}

	queryPool = std::make_unique<SynchronizedQueue<std::unique_ptr<Query>>>(L"DBManager");

	return true;
}

bool DBManager::run() {
    for (auto& db : dbPool) {
        if (db->getState() != DBState::Stop) continue;

		if (!db->connect(ip.c_str(), port, dbName.c_str(), id.c_str(), password.c_str())) {
			ERROR_LOG(L"! db[%s] connection error", dbName.c_str());
			continue;
		}

		if (!db->run()) WARNING_LOG(L"Database couldn't start");
    }

	return true;
}
void DBManager::stopAll() {
	for (auto& db : dbPool) {
		db->setState(DBState::Stop);
	}
}