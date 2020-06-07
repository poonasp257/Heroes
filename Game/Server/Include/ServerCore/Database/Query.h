#ifndef QUERY_H
#define QUERY_H

#include "QueryStatement.h"

class Query {
protected:
	std::unique_ptr<QueryStatement>	statement;

public:
	Query();
	virtual ~Query();
	
	void setStatement(std::unique_ptr<QueryStatement> statement) { 
		this->statement = std::move(statement); 
	}
	QueryStatement* getStatement() { return statement.get(); }

	virtual void doResponse(SQLHSTMT statement) = 0;
};
#endif