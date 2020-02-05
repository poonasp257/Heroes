#include "stdafx.h"
using namespace std;

ConsoleLogger::ConsoleLogger() : Logger() {

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
	wstring text;
	array<wchar_t, SIZE_256> buf;

	vswprintf_s(buf.data(), buf.size(), message, args);

	text = L"[" + logTypes[level] + L"]";
	text += L"[" + convertAnsiToUnicode(Clock::NowTickToStr()) + L"]";
	text += L" ";
	text += buf.data();

	wcout << text << endl;
}