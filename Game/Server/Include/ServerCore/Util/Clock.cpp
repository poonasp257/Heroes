#include "stdafx.h"

LARGE_INTEGER Clock::frequency;
LARGE_INTEGER Clock::startTime;

void Clock::Reset() {
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startTime);
}

float Clock::DeltaTime() {
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);
	float deltaTime = (currentTime.QuadPart - startTime.QuadPart) / (float)frequency.QuadPart;
	startTime = currentTime;
	return deltaTime;
}

std::string Clock::TickToStr(std::time_t tick, const char* format) {
	tm time;
	localtime_s(&time, &tick);
	std::array<char, SIZE_64> timeStr;
	strftime(timeStr.data(), timeStr.size(), format, &time);
	return timeStr.data();
}

std::wstring Clock::TickToWStr(std::time_t tick, const wchar_t* format) {
	tm time;
	localtime_s(&time, &tick);
	std::array<wchar_t, SIZE_64> timeStr;
	wcsftime(timeStr.data(), timeStr.size(), format, &time);
	return timeStr.data();
}

std::time_t Clock::NowTick() {
	timePoint currentTime = system_clock::now();	
	return system_clock::to_time_t(currentTime);
}

std::string Clock::NowTickToStr(const char* format) {
	std::time_t nowTick = NowTick();
	return TickToStr(nowTick, format);
}

std::wstring Clock::NowTickToWStr(const wchar_t* format) {
	std::time_t nowTick = NowTick();
	return TickToWStr(nowTick, format);
}