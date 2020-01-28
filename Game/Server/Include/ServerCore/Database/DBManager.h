#ifndef DBMANAGER_H
#define DBMANAGER_H

class Database;
class Query;

class DBManager : public Singleton <DBManager> {
	int                                 workerCount;
	std::vector<Database*>	            dbPool;

	std::string							ip;
	int									port;
	std::string							dbName;
	std::string							id;
	std::string							password;
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