#include "stdafx.h"
using namespace std;
using namespace filesystem;

FileLogger::FileLogger() : 
	Logger(), 
	path("Log\\") {
	if (!exists(path)) {
		filesystem::create_directory(path);
	}

	const auto& config = ConfigManager::Instance().getConfig();
	if (config["Name"].IsNull()) {
		cout << "\'Name\' document doesn't exist\n";
		return;
	}

	string rename = config["Name"].GetString();
	size_t found = rename.find(".log");
	if (found != string::npos) {
		rename = rename.substr(0, found);
	}

	path += Format("%s_%s.log", rename.c_str(), Clock::NowTickToStr(LOG_DATETIME_FORMAT).c_str());
	outStream.open(path.c_str(), ios::app);
	if (outStream.bad()) {
		cout << "log error, file open fail\n";
		return;
	}
}

FileLogger::~FileLogger() {}

void FileLogger::log(Level level, const wchar_t* message, ...) {
	va_list args;
	va_start(args, message);
	this->log(level, message, args);
	va_end(args);
}

void FileLogger::log(Level level, const wchar_t* message, va_list args) {
	array<wchar_t, SIZE_256> buf;
	vswprintf_s(buf.data(), buf.size(), message, args);

	outStream << Format(L"[%ls][%ls] %ls\n", logTypes[level],
		Clock::NowTickToWStr().c_str(), buf.data());
}