#ifndef CONSOLE_LOGGER_H
#define CONSOLE_LOGGER_H

#include "Logger.h"

class CriticalSection;

class ConsoleLogger : public Logger {
private:
	CriticalSection lock;

public:
	ConsoleLogger();
	~ConsoleLogger();

	virtual void log(Level level, const wchar_t* message, ...);
	virtual void log(Level level, const wchar_t* message, va_list args);
};
#endif