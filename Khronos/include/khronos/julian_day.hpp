#pragma once
/*	julian_day.hpp

	Khronos library Julian Day class declaration.

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.09.25
	Repaced relational operators with <=>

Version 2016.09.30
	Added: Phase List

Version 2015.09.21
	Initial Release


=============================================================

Copyright Garth Santor/Trinh Han

The copyright to the computer program(s) herein
is the property of Garth Santor/Trinh Han, Canada.
The program(s) may be used and/or copied only with
the written permission of Garth Santor/Trinh Han
or in accordance with the terms and conditions
stipulated in the agreement/contract under which
the program(s) have been supplied.
=============================================================*/

#include <cmath>
#include <string>
#include <ostream>

#include <khronos/def.hpp>
#include <khronos/timeofday.hpp>
#include <khronos/utility.hpp>



namespace khronos {

	// Type definitions
	using jd_t = double;

	// VALUES
	constexpr jd_t GREGORIAN_EPOCH = 173'651.6;

	
	// FUNCTIONS

	inline jd_t jd_to_jdn(jd_t jd) {
		return floor(jd + 0.5);
	}

	inline void jd_to_gregorian(jd_t jd, year_t& year, month_t& month, day_t& day) {

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

	inline void jd_to_gregorian(jd_t jd, year_t& year, month_t& month, day_t& day,
								hour_t& hours, minute_t& minutes, second_t& seconds) {

		jd_to_gregorian(jd, year, month, day);

		// TODO Better implementation of the modulo
		tod_to_hms(utility::mod(jd, 1), hours, minutes, seconds);

	}

} // end-of-namespace khronos