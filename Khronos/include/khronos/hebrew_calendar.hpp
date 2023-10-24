#pragma once

/**	@file khronos/hebrew_calendar.hpp
	@author Garth Santor
	@date 2013-09-26

	Hebrew calendar class.
	*/

#include <khronos/def.hpp>
#include <cmath>
#include <khronos/utility.hpp>
#include <khronos/calendar.hpp>
#include <khronos/timeofday.hpp>

#include <khronos/julian_day.hpp>

namespace khronos {

	char const* hebrew_month_name(month_t month);

	month_t hebrew_months_in_year(year_t year);

	day_t hebrew_delay_of_week(year_t year);

	day_t hebrew_delay_of_week(year_t year);

	day_t hebrew_delay_in_adjacent_year(year_t year);

	day_t hebrew_days_in_year(year_t year);

	day_t hebrew_days_in_month(year_t year, month_t month);

	/** Assisting Functions **/

	bool is_hebrew_leapyear(year_t year);


	/** JD Conversion Functions **/

	jd_t hebrew_to_jdn(year_t year, month_t month, day_t day);

	jd_t hebrew_to_jd(year_t year, month_t month, day_t day);

	jd_t hebrew_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second);

	jd_t hebrew_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second);

	void jd_to_hebrew(jd_t jd, year_t& year, month_t& month, day_t& day);

	void jd_to_hebrew(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second);

	class Hebrew {

		year_t year_ = 0;
		month_t month_ = 0;
		day_t day_ = 0;

		hour_t hour_;
		minute_t minute_;
		second_t second_;

	public:

		Hebrew(jd_t jd);

		Hebrew(Jd const& jd_o) : Hebrew(jd_o.jd()) {};

		Hebrew(now_t inclTime = WTIMEOFDAY) : Hebrew(Jd(inclTime)) {};

		operator Jd() const;

	};
	

}