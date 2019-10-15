#include "stdafx.h"
#include "Logger.h"

Logger::Logger() : logTypes({
		{ Unknown, "UNKNOWN" }, { Info, "INFO" },
		{ Warning, "WARNING" }, { Error, "ERROR" }, { Debug, "DEBUG" } }) {}

Logger::~Logger() {}

void Logger::Log(const std::string& message, Level level = Info) {
	this->Log(message.c_str(), level);
}

ConsoleLogger::ConsoleLogger() : Logger() {

}

ConsoleLogger::~ConsoleLogger() {

}

void ConsoleLogger::Log(const char* message, Level level = Info) {
	std::string text;

	text = "[" + logTypes[level] + "]";
//	text += "[" + Clock.Now() + "]";
	text += message;

	// [INFO][2019.10.16 02:55:45] IOCP Server is started... 

	std::cout << text << std::endl;
}

FileLogger::FileLogger(const std::string& fileName)
	: Logger(), output(fileName) {
}

FileLogger::~FileLogger() {
	output.close();
}

void FileLogger::Log(const char* message, Level level = Info) {

}

SystemLogger::SystemLogger() {

}

SystemLogger::~SystemLogger() {

}