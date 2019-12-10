#include "stdafx.h"

Query::Query() {
	statement = new QueryStatement();
}

Query::~Query() {
	if (statement) delete statement;
}