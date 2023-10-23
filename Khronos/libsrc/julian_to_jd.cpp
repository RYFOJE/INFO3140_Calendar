/**	@file Julian_to_jd.cpp
	@author Garth Santor
	@date 2012-09-14

	Date and time library Julian conversion implementations.
	*/

#include <khronos/julian_calendar.hpp>

namespace khronos {

	jd_t julian_to_jd(year_t year, month_t month, day_t day,
		hour_t hour, minute_t minute, second_t second) {

		tod_t time = tod(hour, minute, second);

		return julian_to_jd(year, month, day) + time;

	}
	
	jd_t julian_to_jd(year_t year, month_t month, day_t day) {

		long long a = (14 - month) / 12;
		long long y = year + 4800 - a;
		long long m = month + 12 * a - 3;

		return day + (153 * m + 2) / 5 +
			365 * y + y / 4 - 32083.5;
	}

	jd_t julian_to_jd(Julian const& julian) {

		return julian_to_jd(julian.year(), julian.month(), julian.day(), 
			julian.hour(), julian.minute(), julian.second());

	}
	
}