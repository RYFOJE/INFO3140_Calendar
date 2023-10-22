#pragma once
/*
khronos\gregorian_calendar.hpp
(c) Garth Santor
Created: 2015-09-22
Last Updated: 2015-09-22

Khronos library 'Gregorian calendar' declarations.
*/


#include <khronos/def.hpp>
#include <khronos/calendar.hpp>
#include <khronos/julian_day.hpp>
#include <string>
#include <sstream>
#include <utility>


namespace khronos {
	// LITERALS
	/* UDL - converts a Gregorian year CE to an astronomical Gregorian year. */
	constexpr year_t operator "" _CE(unsigned long long year) {
		return static_cast<year_t>(year);
	}

	/* UDL - converts a Gregorian year BCE to an astronomical Gregorian year. */
	constexpr year_t operator "" _BCE(unsigned long long year) {
		return static_cast<year_t>( (year * -1) + 1);
	}

	// OPERATIONS
	/**	Leap year test for Proleptic Gregorian Calendar.
		@return 'true' if leap year, 'false' if not.
		@param year [in] Astronomical Gregorian year (1 CE = 1, 1 BCE = 0, 2 BCE = -1, etc.)
		*/
	constexpr bool is_gregorian_leapyear(year_t year) {
		// TODO Find a cleaner way of writing the return statement
		return year % 4 == 0 && year % 100 != 0 ||
			year % 400 == 0;
	}

	/** Provide the number of days in the month of the Gregorian Calendar. */
	constexpr day_t gregorian_days_in_month(month_t month, bool isLeapYear) {
		return civil::days_in_month(month, isLeapYear);
	}


	/** Provide the name of the given month in the Gregorian calendar. */
	constexpr char const * gregorian_month_name(month_t month) {
		return civil::month_name_long(month);
	}


	/** Provide the short name of the given month in the Gregorian calendar. */
	constexpr char const * gregorian_short_month_name(month_t month) {
		return civil::month_name_short(month);
	}
	
	/** Returns the amount of days in a gregorian month **/
	constexpr unsigned int gregorian_days_in_month(civil_month_codes_short month, bool is_leapyear) {
		using namespace civil::detail;
		return daysInMonth[is_leapyear][month];
	}

	/** Conversion to Julian Date **/

	jd_t gregorian_to_jd(year_t year, month_t month, day_t dayOfMonth);

	jd_t gregorian_to_jd(year_t year, month_t month, day_t dayOfMonth, hour_t hours, minute_t minutes, second_t seconds);

	// CLASSES
	// --------------------------------------------------------------------------------------

	/**	Proleptic Gregorian Calendar Date class. */

	class Gregorian {
		year_t		year_ = 1;
		month_t		month_ = 1;
		day_t		day_ = 1;
		
		// TODO Maybe use a struct instead of three variables
		hour_t		hour_ = 0;
		minute_t	minute_ = 0;
		second_t	second_ = 0;

	public:

		// CONSTRUCTORS
		
		/**
		 * @brief		Constructor that will build a Gregorian Date based on a Julian Date
		 * @param jd	The Julian date to base the Gregorian object off of
		*/
		Gregorian(Jd const& jd);
		
		/**
		 * @brief				Default constructor that will see if it include WTIMEOFDAY or NOTIMEOFDAY
		 * @param isCurrTime	now_t enum
		*/
		Gregorian(now_t isCurrTime = WTIMEOFDAY);

		Gregorian(jd_t jd);

		Gregorian(year_t year, month_t month, day_t day) :
			year_(year), month_(month), day_(day) {};

		/**
		 * @brief			Constructor that will create a gregorian object including time of day
		 * @param year		Year of the Gregorian Object
		 * @param month		Month of the Gregorian Object
		 * @param day		Days of the Gregorian Object
		 * @param hour		Hours of the Gregorian Object
		 * @param minute	Minutes of the Gregorian Object
		 * @param second	Seconds of the Gregorian Object
		*/
		Gregorian(year_t year, month_t month, day_t day,
			hour_t hour, minute_t minute, second_t second) :
			year_(year), month_(month), day_(day),
			hour_(hour), minute_(minute), second_(second) {};

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

		operator Jd() const;

		std::string to_string() const;

	};
	// OPERATORS
	// ====================
	
	// OPERATORS
	jd_t operator - (Gregorian const& lhs, Gregorian const& rhs);

	Gregorian operator + (Gregorian const& lhs, months const& rhs);

	Gregorian operator - (Gregorian const& lhs, months const& rhs);

	Gregorian operator + (Gregorian const& lhs, years const& rhs);

	Gregorian operator - (Gregorian const& lhs, years const& rhs);

	// FUNCTIONS

	jd_t gregorian_to_jd(const Gregorian g);

	civil_weekday_codes_long day_of_week(const Gregorian g);

	std::ostream& operator << (std::ostream& os, Gregorian const& gregorian);


	// ELEMENT FUNCTIONS

	year_t year(const Gregorian g);

	month_t month(const Gregorian g);

	day_t day(const Gregorian g);

	hour_t hour(const Gregorian g);

	minute_t minute(const Gregorian g);

	second_t second(const Gregorian g);

} // end-of-namespace khronos
