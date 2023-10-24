/**	@file Islamic.cpp
	@author Garth Santor
	@date 2013-09-20

	Islamic calendar class implementation.
	*/

#include <khronos/islamic_calendar.hpp>
#include <khronos/def.hpp>

#include <sstream>


namespace khronos {

	day_t days_in_month_islamic(month_t month, bool isLeapYear) {
		return (month % 2 == 1 || (month == 12 && isLeapYear)) ? 30 : 29;
	}

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



	Islamic operator+(Islamic const& dt, months const& n) {

		year_t year = dt.year() + n.count / 12;
		month_t month = dt.month() + n.count % 12;
		
		int adjust = (month - 1) / 12 + (month - 12) / 12;
		
		year += adjust;
		month -= 12 * adjust;

		day_t day = std::min(dt.day(), days_in_month_islamic(month, year));

		return Islamic(year, month, day, dt.hour(), dt.minute(), dt.second());
	}

	Islamic operator-(Islamic const& dt, months const& n) {

		year_t year = dt.year() - n.count / 12;
		month_t month = dt.month() - n.count % 12;

		int adjust = (month - 1) / 12 - (month - 12) / 12;

		year -= adjust;
		month += 12 * adjust;

		day_t day = std::min(dt.day(), days_in_month_islamic(month, year));
	

		return Islamic(year, month, day, dt.hour(), dt.minute(), dt.second());
	}

	Islamic operator+(Islamic const& dt, years const& n) {

		year_t year = dt.year() + n.count;
		day_t day = (dt.month() == 12 && dt.day() == 30 && !is_islamic_leapyear(year)) ? 29 : dt.day();

		return Islamic(year, dt.month(), day, dt.hour(), dt.minute(), dt.second());
	}

	Islamic operator-(Islamic const& dt, years const& n) {

		year_t year = dt.year() - n.count;
		day_t day = (dt.month() == 12 && dt.day() == 30 && !is_islamic_leapyear(year)) ? 29 : dt.day();

		return Islamic(year, dt.month(), day, dt.hour(), dt.minute(), dt.second());

	}

	std::string Islamic::to_string() const {

		std::stringstream ss;

		return ss.str();

	}
	
}