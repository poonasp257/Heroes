#ifndef FILE_LOGGER_H
#define FILE_LOOGER_H

#include "Logger.h"

class CriticalSection;

class FileLogger : public Logger {
private:
	std::wfstream	fs;
	std::string		path;
	CriticalSection	lock;

public:
	FileLogger();
	~FileLogger();

	virtual void log(Level level, const wchar_t* message, ...);
	virtual void log(Level level, const wchar_t* message, va_list args);
}; 
#endif