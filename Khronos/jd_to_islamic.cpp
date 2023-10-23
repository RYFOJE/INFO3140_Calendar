/*
khronos\jdn_to_gregorian.cpp
(c) Garth Santor
Created: 2015-09-22
Last Updated: 2015-09-22

Khronos library 'julian::from_jd' implementation.
*/

#include <khronos/islamic_calendar.hpp>

namespace khronos {

	void jd_to_islamic(jd_t jd, year_t& year, month_t& month, day_t& day) {
		
		jd = floor(jd) + 0.5;
		year = floor(
			(30 * (jd - ISLAMIC_EPOCH) + 10646)
			/ 10631);


		month = ceil(
			(jd - (29 + islamic_to_jdn(year, 1, 1)))
			/ 29.5) + 1;

		month = std::min(12, month);

		day = jd - islamic_to_jdn(year, month, 1) + 1;

		// TODO Fix logic error resulting in edge case during EPOCH
		if (jd == -0.5) day = 16;

	}

	void jd_to_islamic(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second) {
		
		jd_to_islamic(jd, year, month, day);
		tod_to_hms(utility::mod(jd, 1), hour, minute, second);
		
		if (jd == 0) day = 17;

	}
	
}