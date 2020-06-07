#ifndef SYSTEM_LOGGER_H
#define SYSTEM_LOGGER_H

#include "Logger.h"

#define UNKNOWN_LOG(msg, ...)		SystemLogger::Log(Logger::Level::Unknown, msg, __VA_ARGS__)
#define INFO_LOG(msg, ...)			SystemLogger::Log(Logger::Level::Info, msg, __VA_ARGS__)
#define WARNING_LOG(msg, ...)		SystemLogger::Log(Logger::Level::Warning, msg, __VA_ARGS__)
#define ERROR_LOG(msg, ...)			SystemLogger::Log(Logger::Level::Error, msg, __VA_ARGS__)

#define UNKNOWN_FILE_LOG(msg, ...)	SystemLogger::LogInFile(Logger::Level::Unknown, msg, __VA_ARGS__)
#define INFO_FILE_LOG(msg, ...)		SystemLogger::LogInFile(Logger::Level::Info, msg, __VA_ARGS__)
#define WARNING_FILE_LOG(msg, ...)	SystemLogger::LogInFile(Logger::Level::Warning, msg, __VA_ARGS__)
#define ERROR_FILE_LOG(msg, ...)	SystemLogger::LogInFile(Logger::Level::Error, msg, __VA_ARGS__)

#ifndef _DEBUG
	#define DEBUG_LOG(msg, ...)		SystemLogger::Log(Logger::Level::Debug, msg, __VA_ARGS__)
	#define TRACE(msg, ...)			SystemLogger::Log(Logger::Level::Debug, "[%s:%d] %s", __FILE__, __LINE__, msg, __VA_ARGS__)	
#else
	#define DEBUG_LOG(msg, ...)		
	#define TRACE(msg, ...)		
#endif

class SystemLogger {
private:
	static FileLogger fileLogger;
	static ConsoleLogger consoleLogger;

public:
	static void Log(Logger::Level level, const wchar_t* message, ...);
	static void LogInFile(Logger::Level level, const wchar_t* message, ...);
};
#endif