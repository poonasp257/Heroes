#include "stdafx.h"

ConsoleLogger SystemLogger::consoleLogger;
FileLogger SystemLogger::fileLogger;

void SystemLogger::Log(Logger::Level level, const wchar_t* message, ...) {
	va_list args;
	va_start(args, message);
	consoleLogger.log(level, message, args);
	va_end(args);
}

void SystemLogger::LogInFile(Logger::Level level, const wchar_t* message, ...) {
	va_list args;
	va_start(args, message);
	fileLogger.log(level, message, args);
	va_end(args);
}