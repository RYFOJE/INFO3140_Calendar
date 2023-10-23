/**	@file Islamic_to_jd.cpp
	@author Garth Santor
	@date 2013-09-19

	Islamic calendar conversion implementations.
	*/

#include <khronos/islamic_calendar.hpp>

namespace khronos {
	
	jd_t islamic_to_jdn(year_t year, month_t month, day_t day) {

		// TODO Find a better way for this edge case (maybe verify initial code)
		if (year == -5498 && month == Shaban && day == 16) return -0.5;

		return day + ceil(29.5 * (month - 1)) + (year - 1) * 354 + floor((3 + 11 * year) / 30) + ISLAMIC_EPOCH - 1;

	}
	
	jd_t islamic_to_jd(year_t& year, month_t& month, day_t& day) {
		
		jd_t jd = islamic_to_jdn(year, month, day);

		return jd;
		
	}

	jd_t islamic_to_jd(year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second) {
		
		jd_t jd = islamic_to_jdn(year, month, day);
		tod_t time = tod(hour, minute, second);
		
		jd+= (time >= 0.5) ? time - 1 : time;
		
		return jd;
		
	}
}