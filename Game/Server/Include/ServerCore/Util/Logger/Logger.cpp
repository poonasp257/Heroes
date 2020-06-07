#include "stdafx.h"
#include "Logger.h"

Logger::Logger() : 
	logTypes({ 
		{ Level::Unknown, L"UNKNOWN" }, 
		{ Level::Info, L"INFO" },
		{ Level::Warning, L"WARNING" }, 
		{ Level::Error, L"ERROR" }, 
		{ Level::Debug, L"DEBUG" } }) {
	setlocale(LC_ALL, "");
}

Logger::~Logger() {}