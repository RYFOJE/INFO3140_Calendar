#pragma once

/**	@file khronos/hebrew_calendar.hpp
	@author Garth Santor
	@date 2013-09-26

	Hebrew calendar class.
	*/

#include <khronos/def.hpp>

namespace khronos {

	char const* hebrew_month_name(month_t month);

	jd_t hebrew_to_jd(year_t year, month_t month, day_t day);

	
	

}