#pragma once

/**	@file khronos/julian_calendar.hpp
	@author Garth Santor
	@date 2013-09-19

	Julian calendar functions and class declaration.
	*/

#include <khronos/def.hpp>
#include <khronos/calendar.hpp>
#include <khronos/julian_day.hpp>

namespace khronos {

	// CONSTANTS

	const double JULIAN_EPOCH = 1'721'423.5;

	
	// FUNCTIONS

	/**
	 * @brief		Returns true if the given year is a leap year in the Julian calendar.
	 * @param year	year to test
	 * @return		true if leap year, false if not.
	*/
	bool is_julian_leapyear(year_t year);
	
	day_t julian_days_in_month(month_t month, bool isLeapYear);
	
	constexpr char const* julian_month_name(month_t month)
	{
		return civil::month_name_long(month);
	}

	constexpr char const* julian_short_month_name(month_t month)
	{
		return civil::month_name_short(month);
	}
	
	constexpr jd_t julian_to_jd(year_t year, month_t month, day_t day) {

		long long a = (14 - month) / 12;
		long long y = year + 4800 - a;
		long long m = month + 12 * a - 3;

		return day + (153 * m + 2) / 5 +
			365 * y + y / 4 - 32083.5;
	}

	constexpr jd_t julian_to_jd(year_t year, month_t month, day_t day,
		hour_t hour, minute_t minute, second_t second) {

		tod_t tod = time_of_day(hour, minute, second);

		return julian_to_jd(year, month, day) + tod;

	}
	
}