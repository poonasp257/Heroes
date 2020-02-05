#ifndef CONSOLE_LOGGER_H
#define CONSOLE_LOGGER_H

#include "Logger.h"

class ConsoleLogger : public Logger {
public:
	ConsoleLogger();
	virtual ~ConsoleLogger();

	virtual void log(Level level, const wchar_t* message, ...);
	virtual void log(Level level, const wchar_t* message, va_list args);
};
#endif