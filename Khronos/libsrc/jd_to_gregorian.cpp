/*
khronos\jdn_to_gregorian.cpp
(c) Garth Santor
Created: 2015-09-22
Last Updated: 2015-09-22

Khronos library 'gregorian::from_jdn' implementation.
*/

#include <khronos/gregorian_calendar.hpp>

namespace khronos {

	void jd_to_gregorian(jd_t jd, year_t& year, month_t& month, day_t& day) {

		// TOD Add better handling for Gregorian_Epoch
		if (jd == GREGORIAN_EPOCH) {
			year = 1;
			month = 1;
			day = 1;
			return;
		}

		jd = floor(jd - 0.5) + 0.5;
		long long j = static_cast<long long>(jd + 0.5) + 32044;
		long long g = j / 146097;
		long long dg = j % 146097;
		long long c = (dg / 36524 + 1) * 3 / 4;
		long long dc = dg - c * 36524;
		long long b = dc / 1461;
		long long db = dc % 1461;
		long long a = (db / 365 + 1) * 3 / 4;
		long long da = db - a * 365;
		long long y = g * 400 + c * 100 + b * 4 + a;
		long long m = (da * 5 + 308) / 153 - 2;
		year = y - 4800 + (m + 2) / 12;
		month = (m + 2) % 12 + 1;
		day = static_cast<day_t>(da - (m + 4) * 153 / 5 + 123);
	}

	void jd_to_gregorian(jd_t jd, year_t& year, month_t& month, day_t& day,
		hour_t& hours, minute_t& minutes, second_t& seconds) {

		jd_to_gregorian(jd, year, month, day);

		// TODO Better implementation of the modulo
		tod_to_hms(utility::mod(jd, 1), hours, minutes, seconds);

	}
	
}