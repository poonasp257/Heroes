#include "stdafx.h"
#include "Logger.h"

Logger::Logger() : logTypes({
		{ Unknown, "UNKNOWN" }, { Info, "INFO" },
		{ Warning, "WARNING" }, { Error, "ERROR" }, { Debug, "DEBUG" } }) {}

Logger::~Logger() {}

ConsoleLogger::ConsoleLogger() : Logger() {

}

ConsoleLogger::~ConsoleLogger() {

}

void ConsoleLogger::Log(const char *message, Level level) {
	std::string text;

	text = "[" + logTypes[level] + "]";
	text += "[" + Clock::NowTickToStr() + "]";
	text += " ";
	text += message;

	std::cout << text << std::endl;
}

FileLogger::FileLogger(const std::string& fileName)
	: Logger(), path("Log\\") {
	if (!filesystem::exists(path)) {
		filesystem::create_directory(path);
	}

	std::string rename = fileName;
	size_t found = rename.find(".log");

	if (found != std::string::npos) {
		rename = rename.substr(0, found);
	}

	path += rename + "_";
	path += Clock::NowTickToStr(LOG_DATETIME_FORMAT);
	path += ".log";

	fs.open(path.c_str(), std::ios::out | std::ios::app);
	if (fs.bad()) {
		std::wcout << L"logFile error, file open fail\n";
		// assert
	}
}

FileLogger::~FileLogger() {
	fs.clear();
	fs.close();
}

void FileLogger::Log(const char *message, Level level) {
	std::string text;

	text = "[" + logTypes[level] + "]";
	text += "[" + Clock::NowTickToStr() + "]";
	text += " ";
	text += message;

	fs << text;
	fs.flush();
}

ConsoleLogger SystemLogger::logger;

void SystemLogger::Log(const char *message, Logger::Level level) {
	logger.Log(message, level);
}