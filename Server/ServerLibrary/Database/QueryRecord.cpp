#include "stdafx.h"
#include "QueryRecord.h"

QueryRecord::QueryRecord() {
    record.CreateInstance(__uuidof(ADODB::Recordset));
}

QueryRecord::~QueryRecord() {
	if (!record) return;

    record.Release();
    record = nullptr;
}

void QueryRecord::errorReport(_com_error& e) {
    SystemLogger::Log(Logger::Warning, "* Query error = %s", e.Description());
}

void QueryRecord::operator=(QueryRecord &lvalue) {
	record = lvalue.getRecord();
}

void QueryRecord::operator=(recordPtr &lvalue) {
    record = lvalue;
}

void QueryRecord::close() {
    try {
		if (record != nullptr && this->isOpened()) {
			record->Close();
		}
    }
    catch (_com_error &e){
        this->errorReport(e);
    }
}

bool QueryRecord::isEof() {
	if (!record) return true;

	try {
		return record->EndOfFile ? true : false;
	}
	catch (_com_error &e) {
		this->errorReport(e);
	}

	return false;
}

HRESULT QueryRecord::moveNext() {
	try {
		return record->MoveNext();
	}
	catch (_com_error &e) {
		this->errorReport(e);
	}

	return S_FALSE;
}

HRESULT QueryRecord::movePrevious() {	
	try {
		return record->MovePrevious();
	}
	catch (_com_error &e) {
		this->errorReport(e);
	}

	return S_FALSE;
}

HRESULT QueryRecord::moveFirst() {
	try {
		return record->MoveFirst();
	}
	catch (_com_error &e) {
		this->errorReport(e);
	}

	return S_FALSE;
}

HRESULT QueryRecord::moveLast() {
	try {
		return record->MoveLast();
	}
	catch (_com_error &e) {
		this->errorReport(e);
	}

	return S_FALSE;
}

bool QueryRecord::get(char *fieldName, char *fieldValue) {
	try {
		_variant_t  vtValue;
		vtValue = record->Fields->GetItem(fieldName)->GetValue();
		sprintf_s(fieldValue, SIZE_256, "%s", (LPCSTR)((_bstr_t)vtValue.bstrVal));
		return true;
	}
	catch (_com_error &e) {
		this->errorReport(e);
		SystemLogger::Log(Logger::Warning, "! error query field : %S", fieldName);
	}

	return false;
}

bool QueryRecord::get(char *fieldName, wchar_t *fieldValue) {
	try {
		_variant_t  vtValue;
		vtValue = record->Fields->GetItem(fieldName)->GetValue();
		swprintf_s(fieldValue, SIZE_256, L"%s", (LPWSTR)((_bstr_t)vtValue.bstrVal));
		return true;
	}
	catch (_com_error &e) {
		this->errorReport(e);
		SystemLogger::Log(Logger::Warning, "! error query field : %S", fieldName);
	}
	return false;
}

bool QueryRecord::get(char *fieldName, int32_t& fieldValue) {
	try {
		_variant_t  vtValue;
		vtValue = record->Fields->GetItem(fieldName)->GetValue();
		fieldValue = vtValue.intVal;
		return true;
	}
	catch (_com_error &e) {
		this->errorReport(e);
		SystemLogger::Log(Logger::Warning, "! error query field : %S", fieldName);
	}
	return false;
}

bool QueryRecord::get(char *fieldName, int64_t& fieldValue) {
	try {
		_variant_t  vtValue;
		vtValue = record->Fields->GetItem(fieldName)->GetValue();
		fieldValue = vtValue.intVal;
		return true;
	}
	catch (_com_error &e) {
		this->errorReport(e);
		SystemLogger::Log(Logger::Warning, "! error query field : %S", fieldName);
	}

	return false;
}

bool QueryRecord::get(char *fieldName, float& fieldValue) {
	try {
		_variant_t  vtValue;
		vtValue = record->Fields->GetItem(fieldName)->GetValue();
		fieldValue = vtValue.fltVal;
		return true;
	}
	catch (_com_error &e) {
		this->errorReport(e);
		SystemLogger::Log(Logger::Warning, "! error query field : %S", fieldName);
	}

	return false;
}

bool QueryRecord::get(char *fieldName, double& fieldValue) {
	try {
		_variant_t  vtValue;
		vtValue = record->Fields->GetItem(fieldName)->GetValue();
		fieldValue = vtValue.dblVal;
		return true;
	}
	catch (_com_error &e) {
		this->errorReport(e);
		SystemLogger::Log(Logger::Warning, "! error query field : %S", fieldName);
	}

	return false;
}

bool QueryRecord::get(char *fieldName, long& fieldValue) {
	try {
		_variant_t  vtValue;
		vtValue = record->Fields->GetItem(fieldName)->GetValue();
		fieldValue = vtValue.lVal;
		return true;
	}
	catch (_com_error &e) {
		this->errorReport(e);
		SystemLogger::Log(Logger::Warning, "! error query field : %S", fieldName);
	}

	return false;
}