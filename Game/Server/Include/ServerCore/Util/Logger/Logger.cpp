#include "stdafx.h"
#include "Logger.h"

Logger::Logger() : logTypes({
		{ Unknown, L"UNKNOWN" }, { Info, L"INFO" },
		{ Warning, L"WARNING" }, { Error, L"ERROR" }, { Debug, L"DEBUG" } }) {
	setlocale(LC_ALL, "");
}

Logger::~Logger() {}