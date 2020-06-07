#ifndef LOGGER_H
#define LOGGER_H

class Logger {	
public:
	enum class Level {
		Unknown, Info, Warning, Error, Debug
	};

public:
	Logger();
	virtual ~Logger();

	Logger(const Logger& other) = delete;
	Logger& operator=(const Logger& other) = delete;

	virtual void log(Level level, const wchar_t* message, ...) = 0;
	virtual void log(Level level, const wchar_t* message, va_list args) = 0;

protected:
	std::map<Level, const wchar_t*> logTypes;
};
#endif