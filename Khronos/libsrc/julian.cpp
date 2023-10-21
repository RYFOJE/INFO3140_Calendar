/**	@file Julian.cpp
	@author Garth Santor
	@date 2013-09-19

	Julian calendar class implementation.
	*/

#include <khronos/julian_calendar.hpp>

namespace khronos {

	bool is_julian_leapyear(year_t year) { return year % 4 == 0; }
	
	day_t julian_days_in_month(month_t month, bool isLeapYear)
	{
		return civil::days_in_month(month, isLeapYear);
	}
	
}