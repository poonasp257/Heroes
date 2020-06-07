#include "stdafx.h"
using namespace std;

ConsoleLogger::ConsoleLogger() : 
	Logger(), 
	lock(L"ConsoleLogger") {

}

ConsoleLogger::~ConsoleLogger() {

}

void ConsoleLogger::log(Level level, const wchar_t* message, ...) {
	va_list args;
	va_start(args, message);
	this->log(level, message, args);
	va_end(args);
}

void ConsoleLogger::log(Level level, const wchar_t* message, va_list args) {
	array<wchar_t, SIZE_256> buf;
	vswprintf_s(buf.data(), buf.size(), message, args);
	wstring text = Format(L"[%s][%s] %s", logTypes[level], 
		Clock::NowTickToWStr().c_str(), buf.data());
	SAFE_LOCK(lock);
	wcout << text << endl;
}