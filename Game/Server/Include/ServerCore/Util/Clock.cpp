#include "stdafx.h"

std::string Clock::TickToStr(std::time_t tick, const char *format) {
	std::array<char, SIZE_64> timeStr;
	tm time;

	localtime_s(&time, &tick);
	strftime(timeStr.data(), timeStr.size(), format, &time);

	return std::string(timeStr.data());
}

std::time_t Clock::NowTick() {
	timePoint currentTime = system_clock::now();
	
	return system_clock::to_time_t(currentTime);
}

std::string Clock::NowTickToStr(const char *format) {
	std::time_t nowTick = NowTick();

	return TickToStr(nowTick, format);
}