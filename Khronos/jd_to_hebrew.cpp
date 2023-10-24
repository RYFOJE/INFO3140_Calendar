/**	@file Hebrew_to_jd.cpp
	@author Garth Santor
	@date 2012-09-14

	Hebrew calendar conversion implementations.
	*/

#include <khronos/hebrew_calendar.hpp>

namespace khronos {

	void jd_to_hebrew(jd_t jd, year_t& year, month_t& month, day_t& day)
	{

		jd = floor(jd) + 0.5;

		int count = static_cast<int>(floor((jd - HEBREW_EPOCH) * 98496.0 / 35975351.0));

		year = count - 1;
		int i = count;

		while (jd >= hebrew_to_jdn(i, 7, 1)) {
			i++;
			year++;
		}

		int first = (jd < hebrew_to_jdn(year, 1, 1)) ? 7 : 1;

		month = first;
		i = first;
		
		while (jd > hebrew_to_jdn(year, i, hebrew_days_in_month(year, i))) {
			i++;
			month++;
		}
		
		day = static_cast<day_t>(floor(jd - hebrew_to_jdn(year, month, 1)) + 1);
		

	}

	void jd_to_hebrew(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second)
	{

		jd_to_hebrew(jd, year, month, day);

		tod_t time = jd - floor(jd);

		time = (time < 0.5) ? time + 1 : time;

		tod_to_hms(time, hour, minute, second);
		
	}

}