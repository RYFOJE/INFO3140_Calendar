/**	@file	gregorian.cpp
	@author	Garth Santor
	@date	2013-09-19

	Gregorian calendar class implementation.
	*/

#include <khronos/gregorian_calendar.hpp>
#include <khronos/julian_calendar.hpp>

#include <iomanip>


namespace khronos {

	Gregorian::Gregorian(jd_t jd) {
		jd_to_gregorian(jd, year_, month_, day_, hour_, minute_, second_);

	}

	std::string Gregorian::to_string() const
	{
		using namespace civil;
		std::stringstream ss;

		ss << day_name(day_of_week(*this)) << ", ";
		ss << month_name_long(month_) << " ";
		ss << day_ << " ";
		

		// TODO Find a better way of implementing this
		std::string commonEraNotation = (year_ > 0) ? "CE" : "BCE";
		year_t adjustedYear = (year_ > 0) ? year_ : -year_ + 1; // Can use abs instead but its faster doing it this way as we already need to do a comparaison
		
		ss << adjustedYear << " ";
		ss << commonEraNotation << ", ";


		hour_t formattedHour = (hour_ % 12);
		formattedHour = (formattedHour == 0) ? 12 : formattedHour;
		ss << formattedHour << ":";
		ss << std::setfill('0') << std::setw(2) << minute_ << ":";
		ss << std::setfill('0') << std::setw(2) << second_ << " ";
		
		std::string meridiem = (hour_ < 12) ? "am" : "pm";

		ss << meridiem;

		return ss.str();
	}


	civil_weekday_codes_long day_of_week(const Gregorian g) {

		jd_t jd = gregorian_to_jd(g);
		return day_of_week(jd);
	}

	std::ostream& operator << (std::ostream& os, Gregorian const& gregorian) {
		return os << gregorian.to_string();
	}

	Gregorian operator + (Gregorian const& lhs, months const& rhs) {

		year_t year = lhs.year() + rhs.count / 12;
		month_t month = lhs.month() + rhs.count % 12;
		int adjust = (month - 1) / 12 + (month - 12) / 12;
		year += adjust;
		month -= adjust * 12;
		day_t day = std::min(lhs.day(), gregorian_days_in_month(month, is_gregorian_leapyear(year)));
		
		return Gregorian(year, month, day, lhs.hour(), lhs.minute(), lhs.second());
		
	}
	
	Gregorian operator - (Gregorian const& lhs, months const& rhs) {

		year_t year = lhs.year() - rhs.count / 12;
		month_t month = lhs.month() - rhs.count % 12;
		int adjust = (month - 1) / 12 - (month - 12) / 12;
		year -= adjust;
		month += adjust * 12;
		day_t day = std::min(lhs.day(), gregorian_days_in_month(month, is_gregorian_leapyear(year)));

		return Gregorian(year, month, day, lhs.hour(), lhs.minute(), lhs.second());
		
	}

	Gregorian operator + (Gregorian const& lhs, years const& rhs) {
		year_t year = static_cast<year_t>(lhs.year() + rhs.count);
		month_t month = lhs.month();
		day_t day = (month == 2 && lhs.day() == 29 && !is_gregorian_leapyear(year)) ? 28 : lhs.day();
		
		return Gregorian(year, month, day, lhs.hour(), lhs.minute(), lhs.second());
	}

	Gregorian operator - (Gregorian const& lhs, years const& rhs) {
		year_t year = static_cast<year_t>(lhs.year() - rhs.count);
		month_t month = lhs.month();
		day_t day = (month == 2 && lhs.day() == 28 && !is_gregorian_leapyear(year)) ? 28 : lhs.day();

		return Gregorian(year, month, day, lhs.hour(), lhs.minute(), lhs.second());
	}
	
	Gregorian::operator Jd() const {
		
		return Jd(gregorian_to_jd(year_, month_, day_, hour_, minute_, second_));

	}

	Gregorian::operator Julian() const {
		return Julian(gregorian_to_jd(year_, month_, day_, hour_, minute_, second_));
	}
	

	year_t year(const Gregorian g) { return g.year(); }

	month_t month(const Gregorian g) { return g.month(); }

	day_t day(const Gregorian g) { return g.day(); }

	hour_t hour(const Gregorian g) { return g.hour(); }

	minute_t minute(const Gregorian g) { return g.minute(); }

	second_t second(const Gregorian g) { return g.second(); }

}