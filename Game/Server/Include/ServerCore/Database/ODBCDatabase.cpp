#include "stdafx.h"
#include "Query.h"
#include "DBManager.h"

ODBCDatabase::ODBCDatabase() : 
	Database() {
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

bool ODBCDatabase::connect(const wchar_t* ip, int port, const wchar_t* dbName, const wchar_t* id, const wchar_t* password) {
    this->name = dbName;
	INFO_LOG(L"connect try: %s, %s, %s", dbName, id, password);

	std::array<wchar_t, SIZE_256> connectionStr;
	_snwprintf_s(connectionStr.data(), connectionStr.size(), ((size_t)-1),
		L"DRIVER={SQL Server};SERVER=%s, %d; DATABASE=%s;UID=%s;PWD=%s;",
		ip, port, dbName, id, password);

	SQLRETURN retVal = SQLDriverConnect(dbConnection, NULL,
		 (SQLWCHAR*)connectionStr.data(), SQL_NTS, NULL, 1024, NULL, SQL_DRIVER_NOPROMPT);
	if (retVal != SQL_SUCCESS && retVal != SQL_SUCCESS_WITH_INFO) {
		INFO_LOG(L"[%s] connection failed", dbName);
		return false;
	}

	INFO_LOG(L"[%s] connection success", dbName);

	return true;
}

bool ODBCDatabase::isConnected() {
	SQLUINTEGER uIntVal;
	SQLRETURN retVal = SQLGetConnectAttr(dbConnection, SQL_ATTR_CONNECTION_DEAD,
		(SQLPOINTER)&uIntVal, (SQLINTEGER)sizeof(uIntVal), NULL);

    return uIntVal == SQL_CD_TRUE;
}

bool ODBCDatabase::disconnect() {
	if (!dbConnection) return false;

	if (state == DBState::Stop) return true;

	try {
        this->execute();
        if (!dbConnection) return true;
		
		state = DBState::Stop;
		SQLDisconnect(dbConnection);
		INFO_LOG(L"database close");

		return true;
	} catch (...) {
		ERROR_LOG(L"ODBCDatabase[%s] disconnect fail", name.c_str());
	}

	return false;
}

void ODBCDatabase::prepareStatement(const wchar_t* query) {
	SQLRETURN retVal = SQLAllocHandle(SQL_HANDLE_STMT, dbConnection, &dbStatement);
	if (retVal != SQL_SUCCESS && retVal != SQL_SUCCESS_WITH_INFO) {
		ERROR_LOG(L"statement allocate failed");
		return;
	}

	retVal = SQLPrepare(dbStatement, (SQLWCHAR*)query, SQL_NTS);
	if (retVal != SQL_SUCCESS) {
		ERROR_LOG(L"statement prepare failed");
		return;
	}
}

SQLRETURN ODBCDatabase::executeStatement() {
	if (!dbStatement) return SQL_ERROR;

	SQLRETURN retVal = SQLExecute(dbStatement);
	if (retVal != SQL_SUCCESS) {
		ERROR_LOG(L"prepared statement execute failed");
	}

	return retVal;
}

SQLRETURN ODBCDatabase::executeStatementDirect(const wchar_t* query) {
	SQLRETURN retVal = SQLAllocHandle(SQL_HANDLE_STMT, dbConnection, &dbStatement);
	if (retVal != SQL_SUCCESS && retVal != SQL_SUCCESS_WITH_INFO) {
		ERROR_LOG(L"statement allocate failed");
		return retVal;
	}

	retVal = SQLExecDirect(dbStatement, (SQLWCHAR*)query, SQL_NTS);
	if (retVal != SQL_SUCCESS && retVal != SQL_SUCCESS_WITH_INFO) {
		ERROR_LOG(L"direct statement execute failed");
		return retVal;
	}

	return retVal;
}

void ODBCDatabase::execute() {
	if (DBManager::Instance().isQueryPoolEmpty()) return;

	std::unique_ptr<Query> query = nullptr;
	DBManager::Instance().popQuery(query);
	if (!query) return;
	
	QueryStatement* statement = query->getStatement();
	const wchar_t* sqlQuery = statement->getQuery();

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

	if (retVal != SQL_SUCCESS && retVal != SQL_SUCCESS_WITH_INFO) {
		WARNING_LOG(L"query : [%s] have error code [%d] ", sqlQuery, retVal);
	}
	
	query->doResponse(dbStatement);

	SQLFreeStmt(dbStatement, SQL_CLOSE);
	SQLFreeStmt(dbStatement, SQL_UNBIND);
	SQLFreeStmt(dbStatement, SQL_RESET_PARAMS);
}

void ODBCDatabase::process() {
    while (state != DBState::Stop) {
		this->execute();
		Sleep(1);
    }
}

bool ODBCDatabase::run() {
	state = DBState::Running;
	thread = MAKE_THREAD(ODBCDatabase, process);
	if (thread == nullptr) return false;

	return true;
}