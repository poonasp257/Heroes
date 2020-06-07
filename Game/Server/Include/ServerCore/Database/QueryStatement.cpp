#include "stdafx.h"
#include "QueryStatement.h"

QueryStatement::QueryStatement() :
 	type(QueryType::Direct) {
	paramCount = 0;
	query.clear();
}

QueryStatement::~QueryStatement() {

}

void QueryStatement::setQuery(const wchar_t* query, QueryType type) {
	this->query = query;
	this->type = type;
}

void QueryStatement::addParam(const char* value) {
	this->addArg(L"'%S'", value);
}

void QueryStatement::addParam(const wchar_t* value) {
	this->addArg(L"'%s'", value);
}

void QueryStatement::addParam(Int16 value) {
	this->addArg(L"'%d'", value);
}

void QueryStatement::addParam(UInt16 value) {
	this->addArg(L"'%u'", value);
}

void QueryStatement::addParam(Int32 value) {
	this->addArg(L"'%d'", value);
}

void QueryStatement::addParam(UInt32 value) {
	this->addArg(L"'%u'", value);
}

void QueryStatement::addParam(Int64 value) {
	this->addArg(L"'%lld'", value);
}

void QueryStatement::addParam(UInt64 value) {
	this->addArg(L"'%llu'", value);
}

void QueryStatement::addParam(float value) {
	this->addArg(L"'%f'", value);
}

void QueryStatement::addParam(double value) {
	this->addArg(L"'%lf'", value);
}