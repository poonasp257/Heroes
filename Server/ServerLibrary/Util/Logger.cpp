#include "stdafx.h"
using namespace std;
using namespace filesystem;

Logger::Logger() : logTypes({
		{ Unknown, "UNKNOWN" }, { Info, "INFO" },
		{ Warning, "WARNING" }, { Error, "ERROR" }, { Debug, "DEBUG" } }) {}

Logger::~Logger() {}

ConsoleLogger::ConsoleLogger() : Logger() {

}

ConsoleLogger::~ConsoleLogger() {

}

void ConsoleLogger::Log(Level level, const char* message, ...) {
	va_list args;
	va_start(args, message);

	this->Log(level, message, args);

	va_end(args);
}

void ConsoleLogger::Log(Level level, const char* message, va_list args) {
	std::string text;
	std::array<char, SIZE_128> buf;

	vsprintf_s(buf.data(), buf.size(), message, args);

	text = "[" + logTypes[level] + "]";
	text += "[" + Clock::NowTickToStr() + "]";
	text += " ";
	text += buf.data();

	std::cout << text << std::endl;
}

FileLogger::FileLogger(const std::string& fileName)
	: Logger(), path("Log\\") {

	if (!exists(path)) {
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

void FileLogger::Log(Level level, const char* message, ...) {
	va_list args;
	va_start(args, message);

	this->Log(level, message, args);

	va_end(args);
}

void FileLogger::Log(Level level, const char* message, va_list args) {
	std::string text;

	text = "[" + logTypes[level] + "]";
	text += "[" + Clock::NowTickToStr() + "]";
	text += " ";
	text += message;

	fs << text;
	fs.flush();
}

ConsoleLogger SystemLogger::logger;

void SystemLogger::Log(Logger::Level level, const char *message, ...) {
	va_list args;
	va_start(args, message);

	Log(level, message, args);

	va_end(args);
}

void SystemLogger::Log(Logger::Level level, const char *message, va_list args) {
	logger.Log(level, message, args);
}