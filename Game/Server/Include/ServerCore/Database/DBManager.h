#ifndef DBMANAGER_H
#define DBMANAGER_H

class Database;
class Query;

class DBManager : public Singleton <DBManager> {
	int                                 workerCount;
	std::vector<Database*>	            dbPool;

	std::wstring						ip;
	int									port;
	std::wstring						dbName;
	std::wstring						id;
	std::wstring						password;
	ThreadJobQueue<Query*>				*queryPool;

public:
	DBManager();
	virtual ~DBManager();
	
	bool isQueryPoolEmpty() const { return queryPool->isEmpty(); }
	void pushQuery(Query *query);
	bool popQuery(Query **query);

	void run();
};
#endif