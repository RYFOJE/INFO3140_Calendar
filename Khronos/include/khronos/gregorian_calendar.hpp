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


	// VALUES



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
	constexpr jd_t gregorian_to_jd(year_t year, month_t month, day_t day) {
		//TODO Implement conversion using floating point conversion and not integer based conversion

		year_t y = year - 1;
		int leapAdjust = 0;

		if (month > 2 && is_gregorian_leapyear(month))
			leapAdjust = -1;

		else if (month > 2 && !is_gregorian_leapyear(month))
			leapAdjust = -2;

		return GREGORIAN_EPOCH - 1 + 365 * y + (y / 4.0) - (y / 100.0) + (y / 400) + (((367 * month - 362) / 12) + leapAdjust + day);
	}

	// CLASSES
	// --------------------------------------------------------------------------------------

	/**	Proleptic Gregorian Calendar Date class. */



	// OPERATORS
	// ====================


} // end-of-namespace khronos
