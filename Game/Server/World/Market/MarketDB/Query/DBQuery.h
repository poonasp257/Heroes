#ifndef MARKETDB_QUERY_H
#define MARKETDB_QUERY_H

//class DBAccountInfoQuery : public Query {
//public:
//	UInt64 clientId;
//
//	DBAccountInfoQuery() {
//		statement->setQuery(L"EXEC SearchCharacterList", QueryType::Direct);
//	}
//	virtual ~DBAccountInfoQuery() {}
//
//	void doResponse(SQLHSTMT statement) {
//		DBAccountInfoResponsePacket packet;
//		packet.clientId = clientId;
//
//		UInt16 createdCharacterCount;
//
//		wchar_t familyName[50];
//		wchar_t characterName[50];
//		wchar_t location[50];
//
//		CharacterInfo characterInfo;
//		SQLBindCol(statement, 1, SQL_C_SHORT, &packet.maxCreatableCharacters, sizeof(UINT16), NULL);
//		SQLBindCol(statement, 2, SQL_C_SHORT, &createdCharacterCount, sizeof(UINT16), NULL);
//		SQLBindCol(statement, 3, SQL_C_UBIGINT, &characterInfo.characterId, sizeof(UInt64), NULL);
//		SQLBindCol(statement, 4, SQL_C_LONG, &characterInfo.level, sizeof(UInt32), NULL);
//		SQLBindCol(statement, 5, SQL_C_FLOAT, &characterInfo.exp, sizeof(float), NULL);
//		SQLBindCol(statement, 6, SQL_C_SBIGINT, &characterInfo.currentHp, sizeof(Int64), NULL);
//		SQLBindCol(statement, 7, SQL_C_SBIGINT, &characterInfo.currentMp, sizeof(Int64), NULL);
//		SQLBindCol(statement, 8, SQL_C_SBIGINT, &characterInfo.maxHp, sizeof(Int64), NULL);
//		SQLBindCol(statement, 9, SQL_C_SBIGINT, &characterInfo.maxMp, sizeof(Int64), NULL);
//		SQLBindCol(statement, 10, SQL_C_FLOAT, &characterInfo.position.x, sizeof(float), NULL);
//		SQLBindCol(statement, 11, SQL_C_FLOAT, &characterInfo.position.y, sizeof(float), NULL);
//		SQLBindCol(statement, 12, SQL_C_FLOAT, &characterInfo.position.z, sizeof(float), NULL);
//		SQLBindCol(statement, 13, SQL_C_FLOAT, &characterInfo.rotation.x, sizeof(float), NULL);
//		SQLBindCol(statement, 14, SQL_C_FLOAT, &characterInfo.rotation.y, sizeof(float), NULL);
//		SQLBindCol(statement, 15, SQL_C_FLOAT, &characterInfo.rotation.z, sizeof(float), NULL);
//		SQLBindCol(statement, 16, SQL_C_SHORT, &characterInfo.characterClass, sizeof(UInt16), NULL);
//		SQLBindCol(statement, 17, SQL_C_WCHAR, &familyName, 50, NULL);
//		SQLBindCol(statement, 18, SQL_C_WCHAR, &characterName, 50, NULL);
//		SQLBindCol(statement, 19, SQL_C_WCHAR, &location, 50, NULL);
//
//		SQLRETURN retVal;
//		while (true) {
//			retVal = SQLFetch(statement);
//			if (retVal == SQL_NO_DATA || createdCharacterCount == 0) break;
//
//			characterInfo.familyName = familyName;
//			characterInfo.characterName = characterName;
//			characterInfo.location = location;
//			packet.characterList.push_back(characterInfo);
//		}
//			   
//		SQLFreeStmt(statement, SQL_CLOSE);
//		SQLFreeStmt(statement, SQL_UNBIND);
//		SQLFreeStmt(statement, SQL_RESET_PARAMS);
//
//		Terminal *terminal = TerminalManager::Instance().getTerminal("Game");
//		terminal->sendPacket(&packet);
//	}
//};
#endif