/**	@file Hebrew_to_jd.cpp
	@author Garth Santor
	@date 2012-09-14

	Hebrew calendar conversion implementations.
	*/

#include <khronos/hebrew_calendar.hpp>

namespace khronos {

	jd_t hebrew_to_jdn(year_t year, month_t month, day_t day) {

		jd_t jdn = HEBREW_EPOCH;

		jdn += hebrew_delay_of_week(year);
		jdn += hebrew_delay_in_adjacent_year(year) + day + 1;

		if (month < 7) {
			
			for (month_t i = 7; i <= hebrew_months_in_year(year); ++i) {
				jdn += hebrew_days_in_month(year, i);
			}
			
			for (month_t i = 1; i < month; ++i) {
				jdn += hebrew_days_in_month(year, i);
			}
		}
		else {
			
			for (month_t i = 7; i < month; ++i) {

				day_t d = hebrew_days_in_month(year, i);

				jdn += d;
			}

		}
		
		return jdn;
		

	}

	jd_t hebrew_to_jd(year_t year, month_t month, day_t day)
	{
		return hebrew_to_jdn(year, month, day) + 0.5;
	}

	jd_t hebrew_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second) {

		jd_t jd = hebrew_to_jdn(year, month, day);
		tod_t time = tod(hour, minute, second);
		
		time = (time >= 0.5) ? time - 1 : time;

		return jd + time;

	}

	
	
}