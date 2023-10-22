/*
khronos\jdn_to_gregorian.cpp
(c) Ryan Jennings
Created: 2023-10-22
Last Updated: 2023-10-22

Khronos library 'julian::from_jdn' implementation.
*/

#include <khronos/julian_calendar.hpp>

namespace khronos {

	void jd_to_julian(jd_t jd, year_t& year, month_t& month, day_t& day,
		hour_t& hour, minute_t& minute, second_t& second) {

		jd_to_julian(jd, year, month, day);

		tod_t tod = jd - floor(jd + 0.5);

		tod_to_hms(tod, hour, minute, second);

	}

	void jd_to_julian(jd_t jd, year_t& year, month_t& month, day_t& day) {

		long long a = static_cast<long long>(floor(jd + 0.5));
		long long b = a + 1524;
		long long c = static_cast<long long>(floor((b - 122.1) / 365.25));
		long long d = static_cast<long long>(floor(365.25 * c));
		long long e = static_cast<long long>(floor((b - d) / 30.6001));

		month = static_cast<month_t>(floor(e < 14 ? e - 1 : e - 13));
		year = static_cast<year_t>(floor(month > 2 ? c - 4716 : c - 4715));
		day = static_cast<day_t>(b - d - floor(30.6001 * e));

	}
	
}