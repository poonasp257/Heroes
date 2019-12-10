#include "stdafx.h"

DBManager::DBManager() {
	Json json;
	bool result = json.readFile("config.json");
	if (!result) {
		SystemLogger::Log(Logger::Error, "File could not be opened!");
		// assert
		return;
	}

	Json::Document& document = json.getDocument();
	Json::Value& root = document["App"]["Database"];
	if (root.Empty()) {
		SystemLogger::Log(Logger::Error, "\'Database\' object is not exist");
		// assert
		return;
	}

	ip = root["Ip"].GetString();
	port = root["Port"].GetInt();
	dbName = root["DBName"].GetString();
	id = root["Id"].GetString();
	password = root["Password"].GetString();
	workerCount = root["ThreadCount"].GetInt();
	
	queryPool = new ThreadJobQueue<Query*>();

	for (int i = 0; i < workerCount; ++i) {
		std::array<char, SIZE_128> patch = { 0, };
		Database *db = new ODBCDatabase();
		dbPool.push_back(db);
	}
}

DBManager::~DBManager() {
	if(queryPool) delete queryPool;

    for (auto db : dbPool) {
		if (!db) continue;

        db->disconnect();
		delete db;
    }
}

void DBManager::pushQuery(Query *query) {
    queryPool->push(query);
}

bool DBManager::popQuery(Query **query) {
	queryPool->pop(*query);
	return (*query) != nullptr;
}

void DBManager::run() {
    for (auto db : dbPool) {
        if (db->getState() != DBState::Stop) continue;

		if (!db->connect(ip.c_str(), port, dbName.c_str(), id.c_str(), password.c_str())) {
			SystemLogger::Log(Logger::Error, "! db[%s] connection error", dbName.c_str());
		}

        db->run();
    }
}