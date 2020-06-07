#ifndef DBMANAGER_H
#define DBMANAGER_H

class Database;
class Query;

class DBManager {
private:
	int										workerCount;
	std::vector<std::unique_ptr<Database>>	dbPool;

	std::wstring							ip;
	int										port;
	std::wstring							dbName;
	std::wstring							id;
	std::wstring							password;

	std::unique_ptr<SynchronizedQueue<std::unique_ptr<Query>>> queryPool;

private:
	DBManager();
	~DBManager();

	DBManager(DBManager&&) = delete;
	DBManager(const DBManager&) = delete;
	DBManager& operator=(DBManager&&) = delete;
	DBManager& operator=(const DBManager&) = delete;

public:
	bool isQueryPoolEmpty() const { return queryPool->isEmpty(); }
	void pushQuery(std::unique_ptr<Query> query);
	void popQuery(std::unique_ptr<Query>& query);

	bool initialize();
	bool run();
	void stopAll();

	static auto& Instance() {
		static DBManager instance;
		return instance;
	}
};
#endif