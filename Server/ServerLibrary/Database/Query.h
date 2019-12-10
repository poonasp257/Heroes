#ifndef QUERY_H
#define QUERY_H

#include "QueryStatement.h"

class Query {
protected:
	QueryStatement		*statement;

public:
	Query();
	virtual ~Query();
	
	void setStatement(QueryStatement *statement) { this->statement = statement; }
	QueryStatement* getStatement() { return statement; }

	virtual void doResponse(SQLHSTMT statement) = 0;
};
#endif