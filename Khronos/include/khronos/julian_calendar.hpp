#pragma once

/**	@file khronos/julian_calendar.hpp
	@author Garth Santor
	@date 2013-09-19

	Julian calendar functions and class declaration.
	*/

#include <khronos/def.hpp>
#include <khronos/calendar.hpp>
#include <khronos/julian_day.hpp>
#include <khronos/gregorian_calendar.hpp>

namespace khronos {

	// USER DEFINED LITERALS

	constexpr year_t operator "" _BC(unsigned long long year) {
		return static_cast<year_t>((year * -1) + 1);
	}

	
	// CONSTANTS

	const double JULIAN_EPOCH = 1'721'423.5;

	
	// FUNCTIONS

	/**
	 * @brief		Returns true if the given year is a leap year in the Julian calendar.
	 * @param year	year to test
	 * @return		true if leap year, false if not.
	*/
	bool is_julian_leapyear(year_t year);
	
	day_t julian_days_in_month(month_t month, bool isLeapYear);
	
	constexpr char const* julian_month_name(month_t month)
	{
		return civil::month_name_long(month);
	}

	constexpr char const* julian_short_month_name(month_t month)
	{
		return civil::month_name_short(month);
	}
	
	jd_t julian_to_jd(year_t year, month_t month, day_t day);

	jd_t julian_to_jd(year_t year, month_t month, day_t day,
		hour_t hour, minute_t minute, second_t second);

	jd_t julian_to_jd(Julian const& julian);

	void jd_to_julian(jd_t jd, year_t& year, month_t& month, day_t& day);
	
	void jd_to_julian(jd_t jd, year_t& year, month_t& month, day_t& day,
		hour_t& hour, minute_t& minute, second_t& second);
	

	// JULIAN CLASS

	class Julian {

		year_t year_ = 0;
		month_t month_ = 0;
		day_t day_ = 0;

		hour_t hour_ = 0;
		minute_t minute_ = 0;
		second_t second_ = 0;

	public:
		
		Julian(now_t isCurrTime = WTIMEOFDAY) : Julian(Jd(isCurrTime)) {}

		Julian(jd_t jd);
		
		Julian(Jd const& jd_o) : Julian(jd_o.jd()) {};

		Julian(year_t year, month_t month, day_t day) : year_(year), month_(month), day_(day) {};
		
		Julian(year_t year, month_t month, day_t day,
			hour_t hour, minute_t minute, second_t second) :
			year_(year), month_(month), day_(day), hour_(hour), minute_(minute), second_(second) {};
		
		operator Jd() const;
		operator Gregorian() const;

		// GETTERS

		/*! Get the year.
		\return Astronomical year. */
		constexpr year_t  year() const { return year_; }

		/*! Get the month.
			\return Month number [1..12] */
		constexpr month_t month() const { return month_; }

		/*! Get the day of the month.
			\return Day of month number [1..31]. */
		constexpr day_t day() const { return day_; };

		/*! Get the hour
			\return hour [0 - 23]. */
		constexpr hour_t hour() const { return hour_; };

		/*! Get the hour
			\return hour [0 - 23]. */
		constexpr minute_t minute() const { return minute_; };

		/*! Get the hour
			\return hour [0 - 23]. */
		constexpr second_t second() const { return second_; };

		std::string to_string() const;
		
	};

	// OPERATORS

	Julian operator + (Julian const& jul, months const& month);

	Julian operator - (Julian const& jul, months const& month);

	Julian operator + (Julian const& jul, years const& years);

	Julian operator - (Julian const& jul, years const& years);

	std::ostream& operator << (std::ostream& os, Julian const& gregorian);


	// FUNCTIONS

	year_t year(const Julian j);

	month_t month(const Julian j);

	day_t day(const Julian j);

	hour_t hour(const Julian j);
	
	minute_t minute(const Julian j);

	second_t second(const Julian j);

}