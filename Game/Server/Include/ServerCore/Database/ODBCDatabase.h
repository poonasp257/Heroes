#ifndef ODBCDATABASE_H
#define ODBCDATABASE_H

#include <sqlext.h>
#include "Database.h"

class ODBCDatabase : public Database {
private:
	SQLHENV dbEnviroment;
	SQLHDBC dbConnection;
	SQLHSTMT dbStatement;

	std::wstring			name;
	std::unique_ptr<Thread> thread; 

private:
	void prepareStatement(const wchar_t *query);
	SQLRETURN executeStatement();
	SQLRETURN executeStatementDirect(const wchar_t *query);

	void execute();
	void process();

public:
	ODBCDatabase();
	virtual ~ODBCDatabase();

    bool connect(const wchar_t*ip, int port, const wchar_t*dbName, const wchar_t*id, const wchar_t*password);
	bool disconnect();	
	bool isConnected();
    
	void run();
};
#endif