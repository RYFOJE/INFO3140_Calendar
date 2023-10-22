/*
khronos\gregorian_to_jdn.cpp
(c) Garth Santor
Created: 2015-09-22
Last Updated: 2015-09-22

Khronos library 'gregorian::to_jdn' implementation.
*/

#include <khronos/gregorian_calendar.hpp>
#include <khronos/timeofday.hpp>

namespace khronos {

	jd_t gregorian_to_jd(const Gregorian g) {
		return gregorian_to_jd(g.year(), g.month(), g.day(), g.hour(), g.minute(), g.second());
	}
	
	jd_t gregorian_to_jd(year_t year, month_t month, day_t dayOfMonth) {

		// TODO Find a better fix for this edge case
		if (year == 1 && month == 1 && dayOfMonth == 1) return GREGORIAN_EPOCH;
		
		long long a = (14 - month) / 12;
		long long y = year + 4800 - a;
		long long m = month + 12 * a - 3;
		return dayOfMonth + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045 - 0.5;
	}
	
	jd_t gregorian_to_jd(year_t year, month_t month, day_t dayOfMonth, hour_t hours, minute_t minutes, second_t seconds) {

		// TODO Find a better fix for this edge case
		if (year == 1 && month == 1 && dayOfMonth == 1) return GREGORIAN_EPOCH;

		long long a = (14 - month) / 12;
		long long y = year + 4800 - a;
		long long m = month + 12 * a - 3;
		jd_t jd = dayOfMonth + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045 - 0.5;

		jd += time_of_day(hours, minutes, seconds);

		return jd;
	}
}