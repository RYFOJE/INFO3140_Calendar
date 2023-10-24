/**	@file Hebrew.cpp
	@author Garth Santor
	@date 2013-10-20

	Hebrew calendar class implementation.
	*/

#include <khronos/hebrew_calendar.hpp>

namespace khronos {

	char const* hebrew_month_name(month_t month) {

		return civil::hebrew_month_name(month);
		
	}

	bool is_hebrew_leapyear(year_t year) {

		return utility::mod(7 * year + 1, 19) < 7;

	}

	month_t hebrew_months_in_year(year_t year) {

		return is_hebrew_leapyear(year) ? 13 : 12;

	}

	day_t hebrew_delay_of_week(year_t year) {

		month_t month = floor((235 * year - 234) / 19.0);
		month_t parts = 12084 + 13753 * month;
		day_t day = (month * 29) + floor(parts / 25920.0);
		
		return (utility::mod(3 * (day + 1), 7) < 3) ? day + 1 : day;
		
	}

	day_t hebrew_delay_in_adjacent_year(year_t year) {

		day_t last = hebrew_delay_of_week(year - 1);
		day_t present = hebrew_delay_of_week(year);
		day_t next = hebrew_delay_of_week(year + 1);
		
		day_t days = (next - present) == 356 ? 2 : 0;

		return (next - present) != 356 && (present - last) == 382 ? 1 : days;

	}

	day_t hebrew_days_in_year(year_t year) {

		return hebrew_to_jdn(year + 1, 7, 1) - hebrew_to_jdn(year, 7, 1);

	}

	day_t hebrew_days_in_month(year_t year, month_t month) {

		if (month == 2 || month == 4 || month == 6 || month == 10 || month == 13) {
			return 29;
		}

		else if (month == 12 && !is_hebrew_leapyear(year)) {
			return 29;
		}

		else if (month == 8 && hebrew_days_in_year(year) % 10 != 5) {
			return 29;
		}

		else if (month == 9 && hebrew_days_in_year(year) % 10 == 3) {
			return 29;
		}

		else {
			return 30;
		}

	}

	Hebrew::Hebrew(jd_t jd) {
		
		jd_to_hebrew(jd, year_, month_, day_, hour_, minute_, second_);

	}

	Hebrew::operator Jd() const {

		return Jd(hebrew_to_jd(year_, month_, day_, hour_, minute_, second_));

	};
	
}