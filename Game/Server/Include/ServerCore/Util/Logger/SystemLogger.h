#ifndef SYSTEM_LOGGER_H
#define SYSTEM_LOGGER_H

class SystemLogger {
private:
	static FileLogger fileLogger;
	static ConsoleLogger consoleLogger;

public:
	static void Log(Logger::Level level, const wchar_t* message, ...);
	static void LogInFile(Logger::Level level, const wchar_t* message, ...);
};
#endif