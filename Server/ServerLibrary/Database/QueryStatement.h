#ifndef QUERYSTATEMENT_H
#define QUERYSTATEMENT_H

enum class QueryType {
	Direct, Prepared
};

class QueryStatement {
private:
	QueryType				type;

	std::wstring			query;
    int						paramCount;

private:
	template<typename T>
	void addArg(const wchar_t *fmt, T value) {
		std::array<wchar_t, SIZE_256> buffer;

		_snwprintf_s(buffer.data(), buffer.size(), ((size_t)-1), fmt, value);

		if (paramCount++) query += L", ";
		else query += L" ";

		query += buffer.data();
	}

public:
    QueryStatement();
    ~QueryStatement();

    void setQuery(const wchar_t *query, QueryType type = QueryType::Direct);
	const wchar_t* getQuery() { return query.c_str(); }

	QueryType getType() const { return type; }

    void addParam(const char *value);
	void addParam(const wchar_t *value);
	void addParam(Int16 value);
	void addParam(UInt16 value);
    void addParam(Int32 value);
    void addParam(UInt32 value);
    void addParam(Int64 value);
    void addParam(UInt64 value);
    void addParam(float value);
    void addParam(double value);
};
#endif