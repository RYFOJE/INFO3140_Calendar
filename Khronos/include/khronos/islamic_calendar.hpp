#pragma once

/**	@file khronos/Islamic_calendar.hpp
	@author Garth Santor
	@date 2013-09-19

	Islamic calendar class and functions.
	*/

#include <khronos/def.hpp>
#include <khronos/calendar.hpp>
#include <khronos/timeofday.hpp>

#include <khronos/julian_day.hpp>


namespace khronos {

	jd_t islamic_to_jdn(year_t year, month_t month, day_t day);

	jd_t islamic_to_jd(year_t year, month_t month, day_t day);

	jd_t islamic_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second);
	
	void jd_to_islamic(jd_t jd, year_t& year, month_t& month, day_t& day);

	void jd_to_islamic(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second);
	
	
	
	bool is_islamic_leapyear(year_t year);

	char const* islamic_month_name(month_t month);

	
	class Islamic {

		year_t year_ = 0;
		month_t month_ = 0;
		day_t day_ = 0;

		hour_t hour_ = 0;
		minute_t minute_ = 0;
		second_t second_ = 0;

	public:

		Islamic(now_t includeTime = WTIMEOFDAY) : Islamic(Jd(includeTime)) {};

		Islamic(jd_t jd);

		Islamic(Jd const& jd) : Islamic(jd.jd()) {};

		Islamic(year_t year, month_t month, day_t day) : Islamic(year, month, day, 0, 0, 0) {}
		
		Islamic(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second) :
			year_(year), month_(month), day_(day), hour_(hour), minute_(minute), second_(second) {}
		
		operator Jd() const;

	};


	year_t year(const Islamic i);

	month_t month(const Islamic i);

	day_t day(const Islamic i);

	hour_t hour(const Islamic i);

	minute_t minute(const Islamic i);

	second_t second(const Islamic i);
	
}