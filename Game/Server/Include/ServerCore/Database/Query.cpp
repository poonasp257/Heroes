#include "stdafx.h"

Query::Query() : 
	statement(std::make_unique<QueryStatement>()) {

}

Query::~Query() {

}