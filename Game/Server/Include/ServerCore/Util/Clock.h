#ifndef CLOCK_H
#define CLOCK_H

using namespace std::chrono;

#define DATE_FORMAT				"%Y.%m.%d"
#define TIME_FORMAT				"%H:%M:%S"
#define DATETIME_FORMAT			"%Y.%m.%d %H:%M:%S"
#define LOG_DATETIME_FORMAT		"%Y%m%d_%H%M%S"

#define DATE_FORMAT_W			L"%Y.%m.%d"
#define TIME_FORMAT_W			L"%H:%M:%S"
#define DATETIME_FORMAT_W		L"%Y.%m.%d %H:%M:%S"
#define LOG_DATETIME_FORMAT_W	L"%Y%m%d_%H%M%S"

class Clock {
private:
	static LARGE_INTEGER frequency;
	static LARGE_INTEGER startTime;

public:
	using timePoint = system_clock::time_point;
		
public:
	static void Reset();
	static float DeltaTime();

	static std::string TickToStr(std::time_t tick, const char* format = TIME_FORMAT);
	static std::wstring TickToWStr(std::time_t tick, const wchar_t* format = TIME_FORMAT_W);

	static std::time_t NowTick();
	static std::string NowTickToStr(const char* format = TIME_FORMAT);
	static std::wstring NowTickToWStr(const wchar_t* format = TIME_FORMAT_W);
};

#endif