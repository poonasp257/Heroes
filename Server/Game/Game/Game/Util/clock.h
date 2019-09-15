#ifndef CLOCK_H
#define CLOCK_H

#include "pch.h"

#define CLOCK				Clock::getInstance()
#define NOW_TICK			CLOCK::systemTick()
#define NOW_STRING			CLOCK::nowTime()

#define TICK_MIN			(60)
#define TICK_HOUR			(TICK_MIN * 60)
#define TICK_DAY			(TICK_MIN * 24)

#define TICK_TO_MIN(x)		(x / TICK_MIN)
#define MIN_TO_TICK(x)		(x * TICK_MIN)

#define TICK_TO_HOUR(x)		(x / TICK_HOUR)
#define HOUR_TO_TICK(x)		(x * TICK_HOUR)

#define TICK_TO_DAY(x)		(x / TICK_DAY)
#define DAY_TO_TICK(x)		(x * TICK_DAY)

enum class DayOfTheWeek {
	Sunday, 
	Monday, 
	Tuesday,
	Wednesday, 
	Thursday, 
	Friday, 
	Saturday
};

#define DATETIME_FORMAT		L"D%Y-%m-%dT%H:%M:%S"
#define DATE_FORMAT			L"%Y-%m-%d"
#define TIME_FORMAT			L"%H:%M:%S"
#define DB_TIME_FORMAT		L"%4d-%2d-%2d %2d:%2d:%2d"

typedef std::chrono::system_clock::time_point timePoint;

class Clock : public Singleton<Clock> {
private:
	tick_t serverStartTick;
	wstr_t tickToStr(tick_t tick, const WCHAR *fmt = DATETIME_FORMAT);

};

#endif