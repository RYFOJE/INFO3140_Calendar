#pragma once

/**	@file khronos/Islamic_calendar.hpp
	@author Garth Santor
	@date 2013-09-19

	Islamic calendar class and functions.
	*/

#include <khronos/def.hpp>
#include <khronos/julian_day.hpp>


namespace khronos {

	void islamic_to_jd(jd_t jd, year_t year, month_t month, day_t day);

	void islamic_to_jd(jd_t jd, year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second);
	
	bool is_islamic_leapyear(year_t year);

	char const* islamic_month_name(month_t month);

	


	class Islamic {

		year_t year_;
		month_t month_;
		day_t day_;

		hour_t hour_;
		minute_t minute_;
		second_t second_;

	public:

		Islamic(now_t includeTime = WTIMEOFDAY) : Islamic(Jd(includeTime)) {};

		Islamic(jd_t jd);

		Islamic(Jd const& jd) : Islamic(jd.jd()) {};

		Islamic(year_t year, month_t month, day_t day) : Islamic(year, month, day, 0, 0, 0) {}
		
		Islamic(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second) :
			year_(year), month_(month), day_(day), hour_(hour), minute_(minute), second_(second) {}
		
		

	};


	year_t year(const Islamic i);

	month_t month(const Islamic i);

	day_t day(const Islamic i);

	hour_t hour(const Islamic i);

	minute_t minute(const Islamic i);

	second_t second(const Islamic i);
	
}