#ifndef LOGGER_H
#define LOGGER_H

class Logger {	
public:
	enum Level {
		Unknown, Info, Warning, Error, Debug
	};

public:
	Logger();
	virtual ~Logger();

	Logger(const Logger& other) = delete;
	Logger& operator=(const Logger& other) = delete;

	virtual void Log(Level level, const char *message, ...) = 0;
	virtual void Log(Level level, const char *message, va_list args) = 0;
	
protected:
	std::map<Level, std::string> logTypes;
};
 
class ConsoleLogger : public Logger {
public:
	ConsoleLogger();
	virtual ~ConsoleLogger();

	virtual void Log(Level level, const char *message, ...);
	virtual void Log(Level level, const char *message, va_list args);
};

class FileLogger : public Logger {
private:
	std::fstream fs;
	std::string path;

public:
	FileLogger(const std::string& fileName);
	virtual ~FileLogger();
	
	virtual void Log(Level level, const char *message, ...);
	virtual void Log(Level level, const char *message, va_list args);
};

class SystemLogger {
private:
	static ConsoleLogger logger;

public:
	static void Log(Logger::Level level, const char *message, ...);
	static void Log(Logger::Level level, const char *message, va_list args);
};

#endif