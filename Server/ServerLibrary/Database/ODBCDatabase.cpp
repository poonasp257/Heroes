#include "stdafx.h"
#include "Query.h"
#include "DBManager.h"

ODBCDatabase::ODBCDatabase() : Database() {
    state = DBState::Stop;

	SQLRETURN retVal = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &dbEnviroment);
	if (retVal != SQL_SUCCESS && retVal != SQL_SUCCESS_WITH_INFO) return;

	retVal = SQLSetEnvAttr(dbEnviroment, SQL_ATTR_ODBC_VERSION, (SQLPOINTER*)SQL_OV_ODBC3, 0);
	if (retVal != SQL_SUCCESS && retVal != SQL_SUCCESS_WITH_INFO) return;
	
	retVal = SQLAllocHandle(SQL_HANDLE_DBC, dbEnviroment, &dbConnection);
	if (retVal != SQL_SUCCESS && retVal != SQL_SUCCESS_WITH_INFO) return;
}

ODBCDatabase::~ODBCDatabase() {
    this->disconnect();

	if (dbStatement) {
		SQLFreeHandle(SQL_HANDLE_STMT, dbStatement);
		dbStatement = NULL;
	}
    if (dbConnection) {
		SQLFreeHandle(SQL_HANDLE_DBC, dbConnection);
		dbConnection = NULL;
    }
	if (dbEnviroment) {
		SQLFreeHandle(SQL_HANDLE_ENV, dbEnviroment);
		dbEnviroment = NULL;
	}
}

bool ODBCDatabase::connect(const char *ip, int port, const char *dbName, const char *id, const char *password) {
    this->name = dbName;
	SystemLogger::Log(Logger::Info, "* connect try: %s, %s, %s", dbName, id, password);

	/*SQLSMALLINT outConnectionLen;
	std::array<char, SIZE_256> outConnectionStr;
	std::array<char, SIZE_256> connectionStr;
	_snprintf_s(connectionStr.data(), connectionStr.size(), ((size_t)-1),
		"DRIVER={SQL Server};SERVER=%s, %d; DATABASE=%s,UID=%s;PWD=%s;",
		ip, port, dbName, id, password);
		
	 SQLRETURN retVal = SQLDriverConnectA(
		 dbConnection, NULL,
		 (SQLCHAR*)connectionStr.data(), strlen(connectionStr.data()) + 1,
		 (SQLCHAR*)outConnectionStr.data(),  outConnectionStr.size(),
		 &outConnectionLen, SQL_DRIVER_NOPROMPT);*/
	SQLRETURN retVal = SQLConnectA(dbConnection, (SQLCHAR*)dbName, SQL_NTS,
		(SQLCHAR*)id, SQL_NTS, (SQLCHAR*)password, SQL_NTS);
	if (retVal != SQL_SUCCESS && retVal != SQL_SUCCESS_WITH_INFO) {
		SystemLogger::Log(Logger::Info, "* [%s] connection failed", dbName);
		return false;
	}

	SystemLogger::Log(Logger::Info, "* [%s] connection success", dbName);
	return true;
}

bool ODBCDatabase::isConnected() {
	SQLUINTEGER uIntVal;
	SQLRETURN retVal = SQLGetConnectAttr(dbConnection, SQL_ATTR_CONNECTION_DEAD,
		(SQLPOINTER)&uIntVal, (SQLINTEGER) sizeof(uIntVal), NULL);

    return uIntVal == SQL_CD_TRUE ? true : false;
}

bool ODBCDatabase::disconnect() {
	if (!dbConnection) return false;

	if (state == DBState::Stop) return true;

	try {
        this->execute();
        if (!dbConnection) return true;

		SQLDisconnect(dbConnection);
        state = DBState::Stop;
		
        name.clear();

		SystemLogger::Log(Logger::Info, "* database close");

		return true;
	} catch (...) {
		SystemLogger::Log(Logger::Error, "! ODBCDatabase[%s] disconnect fail", name.c_str());
	}

	return false;
}

void ODBCDatabase::prepareStatement(const wchar_t *query) {
	SQLRETURN retVal = SQLAllocHandle(SQL_HANDLE_STMT, dbConnection, &dbStatement);
	if (retVal != SQL_SUCCESS && retVal != SQL_SUCCESS_WITH_INFO) {
		SystemLogger::Log(Logger::Error, "* statement allocate failed");
		return;
	}

	retVal = SQLPrepare(dbStatement, (SQLWCHAR*)query, SQL_NTS);
	if (retVal != SQL_SUCCESS) {
		SystemLogger::Log(Logger::Error, "* statement prepare failed");
		return;
	}
}

SQLRETURN ODBCDatabase::executeStatement() {
	if (!dbStatement) return SQL_ERROR;

	SQLRETURN retVal = SQLExecute(dbStatement);
	if (retVal != SQL_SUCCESS) {
		SystemLogger::Log(Logger::Error, "* prepared statement execute failed");
	}

	return retVal;
}

SQLRETURN ODBCDatabase::executeStatementDirect(const wchar_t *query) {
	SQLRETURN retVal = SQLAllocHandle(SQL_HANDLE_STMT, dbConnection, &dbStatement);
	if (retVal != SQL_SUCCESS && retVal != SQL_SUCCESS_WITH_INFO) {
		SystemLogger::Log(Logger::Error, "* statement allocate failed");
		return retVal;
	}

	retVal = SQLExecDirect(dbStatement, (SQLWCHAR*)query, SQL_NTS);
	if (retVal != SQL_SUCCESS && retVal != SQL_SUCCESS_WITH_INFO) {
		SystemLogger::Log(Logger::Error, "* direct statement execute failed");
		return retVal;
	}
}

void ODBCDatabase::execute() {
	if (DBManager::Instance().isQueryPoolEmpty()) return;

	Query *query = nullptr;
	if (DBManager::Instance().popQuery(&query) == false) {
		return;
	}
	
	QueryStatement *statement = query->getStatement();
	const wchar_t *sqlQuery = statement->getQuery();
	
	state = DBState::Running;
	SQLRETURN retVal;

	switch (statement->getType()) {
	case QueryType::Direct:
		retVal = executeStatementDirect(sqlQuery);
		break;
	case QueryType::Prepared:
		prepareStatement(sqlQuery);
		retVal = executeStatement();
		break;
	}

	state = DBState::StandBy;

	if (retVal != SQL_SUCCESS && retVal != SQL_SUCCESS_WITH_INFO) {
		SystemLogger::Log(Logger::Warning, "* query : [%s] have error code [%d] ", sqlQuery, retVal);
	}
	
	query->doResponse(dbStatement);
	if (query) delete query;
}

void ODBCDatabase::process() {
    while (true) {
		/*if (!this->isConnected()) {
			SystemLogger::Log(Logger::Info, "! db[%s] connection disconnect", name.c_str());
			continue;
		}*/

		this->execute();
		Sleep(1);
    }
}

void ODBCDatabase::run() {
	thread = std::make_unique<Thread>(new std::thread(&ODBCDatabase::process, this));
}