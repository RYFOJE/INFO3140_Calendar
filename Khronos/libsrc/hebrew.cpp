/**	@file Hebrew.cpp
	@author Garth Santor
	@date 2013-10-20

	Hebrew calendar class implementation.
	*/

#include <khronos/hebrew_calendar.hpp>
#include <khronos/calendar.hpp>

namespace khronos {

	char const* hebrew_month_name(month_t month) {

		return civil::hebrew_month_name(month);
		
	}
	
}