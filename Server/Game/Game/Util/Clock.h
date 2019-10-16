#ifndef CLOCK_H
#define CLOCK_H

using namespace std::chrono;

#define DATE_FORMAT				"%Y.%m.%d"
#define TIME_FORMAT				"%H:%M:%S"
#define DATETIME_FORMAT			"%Y.%m.%d %H:%M:%S"
#define LOG_DATETIME_FORMAT		"%Y%m%d_%H%M%S"

class Clock {
public:
	using timePoint = system_clock::time_point;
		
public:
	static std::time_t NowTick();
	static std::string NowTickToStr(const char *format = DATETIME_FORMAT);

	static std::string TickToStr(std::time_t tick, const char *format = DATETIME_FORMAT);
};

#endif