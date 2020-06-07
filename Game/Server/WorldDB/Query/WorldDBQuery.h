#ifndef WORLD_DB_QUERY_H
#define WORLD_DB_QUERY_H

class Session;

class SearchAccountQuery : public Query {
public:
	Session* session;
	objectId_t clientId;

	SearchAccountQuery() {
		statement->setQuery(L"EXEC SearchAccount", QueryType::Direct);
	}
	~SearchAccountQuery() {}

	virtual void doResponse(SQLHSTMT statement) {
		DBSearchAccountResponsePacket packet;
		packet.clientId = clientId;
		packet.errorCode = StatusCode::Fail;

		wchar_t familyName[30] = L"";
		SQLBindCol(statement, 1, SQL_C_WCHAR, familyName, 30, NULL);
		SQLBindCol(statement, 2, SQL_C_SHORT, &packet.creatableCharactersCount, sizeof(UINT16), NULL);

		SQLRETURN retVal = SQLFetch(statement);
		if (retVal == SQL_ERROR) {
			ERROR_LOG(L"*SQL Fetch error");
			return;
		}

		SQLLEN rowCount = 0;
		SQLRowCount(statement, &rowCount);
		if (rowCount > 0) {
			packet.familyName = familyName;
			packet.errorCode = StatusCode::Success;
		}

		session->sendPacket(packet);		
	}
};

class CreateAccountQuery : public Query {
public:
	Session* session;
	objectId_t clientId;
	
	CreateAccountQuery() {
		statement->setQuery(L"EXEC CreateAccount", QueryType::Direct);
	}
	~CreateAccountQuery() {}

	virtual void doResponse(SQLHSTMT statement) {
		DBCreateAccountResponsePacket packet;
		packet.clientId = clientId;
		packet.errorCode = StatusCode::Fail;

		SQLLEN rowCount = 0;
		SQLRowCount(statement, &rowCount);
		if (rowCount > 0) packet.errorCode = StatusCode::Success;

		session->sendPacket(packet);
	}
};

class GetCharacterListQuery : public Query {
public:
	Session* session;
	objectId_t clientId;

	GetCharacterListQuery() {
		statement->setQuery(L"EXEC GetCharacterList", QueryType::Direct);
	}
	~GetCharacterListQuery() {}

	virtual void doResponse(SQLHSTMT statement) {
		DBGetCharacterListResponsePacket packet;
		packet.clientId = clientId;

		CharacterInfo characterInfo;
		wchar_t characterName[30];
		wchar_t location[50];
		SQLBindCol(statement, 1, SQL_C_UBIGINT, &characterInfo.id, sizeof(objectId_t), NULL);
		SQLBindCol(statement, 2, SQL_C_WCHAR, &characterName, 30, NULL);
		SQLBindCol(statement, 3, SQL_C_SHORT, &characterInfo.type, sizeof(UInt16), NULL);
		SQLBindCol(statement, 4, SQL_C_LONG, &characterInfo.level, sizeof(UInt32), NULL);
		SQLBindCol(statement, 5, SQL_C_FLOAT, &characterInfo.exp, sizeof(float), NULL);
		SQLBindCol(statement, 6, SQL_C_SBIGINT, &characterInfo.currentHp, sizeof(Int64), NULL);
		SQLBindCol(statement, 7, SQL_C_SBIGINT, &characterInfo.currentMp, sizeof(Int64), NULL);
		SQLBindCol(statement, 8, SQL_C_FLOAT, &characterInfo.position.x, sizeof(float), NULL);
		SQLBindCol(statement, 9, SQL_C_FLOAT, &characterInfo.position.y, sizeof(float), NULL);
		SQLBindCol(statement, 10, SQL_C_FLOAT, &characterInfo.position.z, sizeof(float), NULL);
		SQLBindCol(statement, 11, SQL_C_FLOAT, &characterInfo.rotation.x, sizeof(float), NULL);
		SQLBindCol(statement, 12, SQL_C_FLOAT, &characterInfo.rotation.y, sizeof(float), NULL);
		SQLBindCol(statement, 13, SQL_C_FLOAT, &characterInfo.rotation.z, sizeof(float), NULL);
		SQLBindCol(statement, 14, SQL_C_WCHAR, &location, 50, NULL);

		SQLRETURN retVal;
		while (SQLFetch(statement) != SQL_NO_DATA) {
			characterInfo.name = characterName;
			characterInfo.location = location;
			packet.characterList.push_back(characterInfo);
		}

		session->sendPacket(packet);
	}
};

class ChangeCharacterOrderQuery : public Query {
public:
	Session* session;
	objectId_t clientId;
	UInt16 fromIndex;
	UInt16 toIndex;
		
	ChangeCharacterOrderQuery() {
		statement->setQuery(L"EXEC ChangeCharacterOrder", QueryType::Direct);
	}
	~ChangeCharacterOrderQuery() {}

	virtual void doResponse(SQLHSTMT statement) {
		DBChangeCharacterOrderResponsePacket packet;
		packet.clientId = clientId;
		packet.fromIndex = fromIndex;
		packet.toIndex = toIndex;

		SQLLEN rowCount = 0;
		SQLRowCount(statement, &rowCount);
		SQLRETURN retVal = SQLRowCount(statement, &rowCount);
		if (retVal == SQL_ERROR) {
			ERROR_LOG(L"* DB Query error!");
			return;
		}

		session->sendPacket(packet);
	}
};

class CreateCharacterQuery : public Query {
public:
	Session* session;
	objectId_t clientId;

	CreateCharacterQuery() {
		statement->setQuery(L"EXEC CreateCharacter", QueryType::Direct);
	}
	~CreateCharacterQuery() {}

	virtual void doResponse(SQLHSTMT statement) {
		DBCreateCharacterResponsePacket packet;
		packet.clientId = clientId;
		packet.errorCode = StatusCode::Success;
		
		SQLLEN rowCount;
		SQLRETURN retVal = SQLRowCount(statement, &rowCount);
		if (retVal == SQL_ERROR) {
			ERROR_LOG(L"* DB Query error!");
		}
		
		if (rowCount < 0) packet.errorCode = StatusCode::Conflict;
		session->sendPacket(packet);
	}
};

class DeleteCharacterQuery : public Query {
public:
	Session* session;
	objectId_t clientId;

	DeleteCharacterQuery() {
		statement->setQuery(L"EXEC DeleteCharacter", QueryType::Direct);
	}
	~DeleteCharacterQuery() {}

	virtual void doResponse(SQLHSTMT statement) {
		DBDeleteCharacterResponsePacket packet;
		packet.clientId = clientId;

		SQLLEN rowCount;
		SQLRETURN retVal = SQLRowCount(statement, &rowCount);
		if (retVal == SQL_ERROR) {
			ERROR_LOG(L"* DB Query error!");
			return;
		}

		if (rowCount < 0) {
			ERROR_LOG(L"* does not exists character");
		}

		session->sendPacket(packet);
	}
};

class UpdateCharacterStatusQuery : public Query {
public:
	UpdateCharacterStatusQuery() {
		statement->setQuery(L"EXEC UpdateCharacterStatus", QueryType::Direct);
	}
	~UpdateCharacterStatusQuery() {}

	virtual void doResponse(SQLHSTMT statement) { }
};

#endif