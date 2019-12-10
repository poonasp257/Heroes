#ifndef QUERYRECORD_H
#define QUERYRECORD_H

#include "Database.h"

class QueryRecord {
private:
	recordPtr		record;
	int				retVal;

public:	
    QueryRecord();
    ~QueryRecord();

    void errorReport(_com_error& e);

    void operator=(QueryRecord& lvalue);
    void operator=(recordPtr& lvalue);

    bool        isOpened() const { return record->State == ADODB::adStateOpen ? true : false; }
    void        close();

	recordPtr	getRecord() { return record; }
	void        setRecord(recordPtr record) { this->record = record; }

	bool		isEof();

	int			getResult() const { return retVal; }
	void		setResult(int result) { retVal = result; }

	HRESULT		moveNext();
	HRESULT		movePrevious();
	HRESULT		moveFirst();
	HRESULT		moveLast();

	bool		get(char *fieldName, char *fieldValue);
	bool		get(char *fieldName, wchar_t* fieldValue);
	bool		get(char *fieldName, int32_t& fieldValue);
	bool		get(char *fieldName, int64_t& fieldValue);
	bool		get(char *fieldName, float& fieldValue);
	bool		get(char *fieldName, double& fieldValue);
	bool		get(char *fieldName, long& fieldValue);
};
#endif