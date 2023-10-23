/**	@file Islamic.cpp
	@author Garth Santor
	@date 2013-09-20

	Islamic calendar class implementation.
	*/

#include <khronos/islamic_calendar.hpp>
#include <khronos/def.hpp>


namespace khronos {

	bool is_islamic_leapyear(year_t year) {

		return (11 * year + 14) % 30 < 11;
		
	}

	char const* islamic_month_name(month_t month) {
		return civil::islamic_month_name(month);
	}
	
	Islamic::Islamic(jd_t jd) {

		jd_to_islamic(jd, year_, month_, day_, hour_, minute_, second_);

	}

	Islamic::operator Jd() const {
		
		return Jd(islamic_to_jd(year_, month_, day_, hour_, minute_, second_));
		
	}
	
}