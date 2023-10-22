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
	
	constexpr jd_t julian_to_jd(year_t year, month_t month, day_t day) {

		long long a = (14 - month) / 12;
		long long y = year + 4800 - a;
		long long m = month + 12 * a - 3;

		return day + (153 * m + 2) / 5 +
			365 * y + y / 4 - 32083.5;
	}

	constexpr jd_t julian_to_jd(year_t year, month_t month, day_t day,
		hour_t hour, minute_t minute, second_t second) {

		tod_t tod = time_of_day(hour, minute, second);

		return julian_to_jd(year, month, day) + tod;

	}

	inline void jd_to_julian(jd_t jd, year_t& year, month_t& month, day_t& day) {

		long long a = static_cast<long long>(floor(jd + 0.5));
		long long b = a + 1524;
		long long c = static_cast<long long>(floor((b - 122.1) / 365.25));
		long long d = static_cast<long long>(floor(365.25 * c));
		long long e = static_cast<long long>(floor((b - d) / 30.6001));
		
		month = static_cast<month_t>(floor(e < 14 ? e - 1 : e - 13));
		year = static_cast<year_t>(floor(month > 2 ? c - 4716 : c - 4715));
		day = static_cast<day_t>(b - d - floor(30.6001 * e));
		
	}
	
	inline void jd_to_julian(jd_t jd, year_t& year, month_t& month, day_t& day,
		hour_t& hour, minute_t& minute, second_t& second) {

		jd_to_julian(jd, year, month, day);

		tod_t tod = jd - floor(jd + 0.5);

		tod_to_hms(tod, hour, minute, second);

	}
	

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
		Julian(Jd jd_o) : Julian(jd_o.jd()) {}; // Error happens when calling the constructor here
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

}