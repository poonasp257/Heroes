#ifndef GAMEDB_QUERY_H
#define GAMEDB_QUERY_H

class Session;

class SearchAccountQuery : public Query {
public:
	Session *session;
	UInt64 clientId;

	SearchAccountQuery() {
		statement->setQuery(L"EXEC SearchAccount", QueryType::Direct);
	}
	virtual ~SearchAccountQuery() {}

	void doResponse(SQLHSTMT statement) {
		DBSearchAccountResponsePacket packet;
		packet.clientId = clientId;
		packet.errorCode = ErrorCode::Fail;

		wchar_t familyName[50] = L"";

		SQLBindCol(statement, 1, SQL_C_WCHAR, familyName, 50, NULL);
		SQLBindCol(statement, 2, SQL_C_SHORT, &packet.creatableCharactersCount, sizeof(UINT16), NULL);

		SQLRETURN retVal = SQLFetch(statement);
		if (retVal == SQL_ERROR) {
			SystemLogger::Log(Logger::Error, L"*SQL Fetch error");
			return;
		}

		SQLLEN rowCount = 0;
		SQLRowCount(statement, &rowCount);
		if (rowCount > 0) {
			packet.familyName = familyName;
			packet.errorCode = ErrorCode::Success;
		}

		session->sendPacket(&packet);		
	}
};

class CreateAccountQuery : public Query {
public:
	Session* session;
	UInt64 clientId;
	
	CreateAccountQuery() {
		statement->setQuery(L"EXEC CreateAccount", QueryType::Direct);
	}
	virtual ~CreateAccountQuery() {}

	void doResponse(SQLHSTMT statement) {
		DBCreateAccountResponsePacket packet;
		packet.clientId = clientId;
		packet.errorCode = ErrorCode::Success;

		SQLLEN rowCount = 0;
		SQLRowCount(statement, &rowCount);
		if (rowCount == 0) packet.errorCode = ErrorCode::Conflict;
		else if (rowCount < 0) packet.errorCode = ErrorCode::Fail;

		session->sendPacket(&packet);
	}
};

class GetCharacterListQuery : public Query {
public:
	Session *session;
	UInt64 clientId;

	GetCharacterListQuery() {
		statement->setQuery(L"EXEC GetCharacterList", QueryType::Direct);
	}
	virtual ~GetCharacterListQuery() {}

	void doResponse(SQLHSTMT statement) {
		DBGetCharacterListResponsePacket packet;
		packet.clientId = clientId;

		CharacterInfo characterInfo;
		wchar_t characterName[50];
		wchar_t location[50];

		SQLBindCol(statement, 1, SQL_C_UBIGINT, &characterInfo.characterId, sizeof(UInt64), NULL);
		SQLBindCol(statement, 2, SQL_C_WCHAR, &characterName, 50, NULL);
		SQLBindCol(statement, 3, SQL_C_SHORT, &characterInfo.characterClass, sizeof(UInt16), NULL);
		SQLBindCol(statement, 4, SQL_C_LONG, &characterInfo.level, sizeof(UInt32), NULL);
		SQLBindCol(statement, 5, SQL_C_FLOAT, &characterInfo.exp, sizeof(float), NULL);
		SQLBindCol(statement, 6, SQL_C_SBIGINT, &characterInfo.currentHp, sizeof(Int64), NULL);
		SQLBindCol(statement, 7, SQL_C_SBIGINT, &characterInfo.currentMp, sizeof(Int64), NULL);
		SQLBindCol(statement, 8, SQL_C_SBIGINT, &characterInfo.maxHp, sizeof(Int64), NULL);
		SQLBindCol(statement, 9, SQL_C_SBIGINT, &characterInfo.maxMp, sizeof(Int64), NULL);
		SQLBindCol(statement, 10, SQL_C_FLOAT, &characterInfo.position.x, sizeof(float), NULL);
		SQLBindCol(statement, 11, SQL_C_FLOAT, &characterInfo.position.y, sizeof(float), NULL);
		SQLBindCol(statement, 12, SQL_C_FLOAT, &characterInfo.position.z, sizeof(float), NULL);
		SQLBindCol(statement, 13, SQL_C_FLOAT, &characterInfo.rotation.x, sizeof(float), NULL);
		SQLBindCol(statement, 14, SQL_C_FLOAT, &characterInfo.rotation.y, sizeof(float), NULL);
		SQLBindCol(statement, 15, SQL_C_FLOAT, &characterInfo.rotation.z, sizeof(float), NULL);
		SQLBindCol(statement, 16, SQL_C_WCHAR, &location, 50, NULL);

		SQLRETURN retVal;
		while (SQLFetch(statement) != SQL_NO_DATA) {
			characterInfo.characterName = characterName;
			characterInfo.location = location;
			packet.characterList.push_back(characterInfo);
		}

		session->sendPacket(&packet);
	}
};

class ChangeCharacterOrderQuery : public Query {
public:
	Session *session;
	UInt64 clientId;
	UInt16 fromIndex;
	UInt16 toIndex;
		
	ChangeCharacterOrderQuery() {
		statement->setQuery(L"EXEC ChangeCharacterOrder", QueryType::Direct);
	}
	virtual ~ChangeCharacterOrderQuery() {}

	void doResponse(SQLHSTMT statement) {
		DBChangeCharacterOrderResponsePacket packet;
		packet.clientId = clientId;
		packet.fromIndex = fromIndex;
		packet.toIndex = toIndex;

		SQLLEN rowCount = 0;
		SQLRowCount(statement, &rowCount);
		if (rowCount <= 0) {
			SystemLogger::Log(Logger::Warning, L"'ChangeCharacterOrder' query error");
		}

		session->sendPacket(&packet);
	}
};

class CreateCharacterQuery : public Query {
public:
	Session *session;
	UInt64 clientId;

	CreateCharacterQuery() {
		statement->setQuery(L"EXEC CreateCharacter", QueryType::Direct);
	}
	virtual ~CreateCharacterQuery() {}

	void doResponse(SQLHSTMT statement) {
		DBCreateCharacterResponsePacket packet;
		packet.clientId = clientId;
		packet.errorCode = ErrorCode::Success;
		
		SQLINTEGER rowCount;
		SQLRowCount(statement, &rowCount);
		if (rowCount == 0) packet.errorCode = ErrorCode::Conflict;
		else if (rowCount < 0) packet.errorCode = ErrorCode::Fail;

		SQLFreeStmt(statement, SQL_CLOSE);
		SQLFreeStmt(statement, SQL_UNBIND);
		SQLFreeStmt(statement, SQL_RESET_PARAMS);

		session->sendPacket(&packet);
	}
};

class DeleteCharacterQuery : public Query {
public:
	Session* session;
	UInt64 clientId;

	DeleteCharacterQuery() {
		statement->setQuery(L"EXEC DeleteCharacter", QueryType::Direct);
	}
	virtual ~DeleteCharacterQuery() {}

	void doResponse(SQLHSTMT statement) {
		DBDeleteCharacterResponsePacket packet;
		packet.clientId = clientId;

		SQLINTEGER rowCount;
		SQLRETURN retVal = SQLRowCount(statement, &rowCount);
		if (retVal == SQL_ERROR) {
			SystemLogger::Log(Logger::Error, L"* DB Query error!");
		}

		if (rowCount < 0) {
			SystemLogger::Log(Logger::Error, L"* does not exists character");
		}

		SQLFreeStmt(statement, SQL_CLOSE);
		SQLFreeStmt(statement, SQL_UNBIND);
		SQLFreeStmt(statement, SQL_RESET_PARAMS);

		session->sendPacket(&packet);
	}
};
#endif