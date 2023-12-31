/**	@file Julian.cpp
	@author Garth Santor
	@date 2013-09-19

	Julian calendar class implementation.
	*/

#include <khronos/julian_calendar.hpp>
#include <iomanip>

namespace khronos {

	Julian::Julian(jd_t jd) {
		
		jd_to_julian(jd, year_, month_, day_, hour_, minute_, second_);
		
	}

	std::string Julian::to_string() const {
		using namespace civil;
		std::stringstream ss;

		ss << day_name(day_of_week(julian_to_jd(year_, month_, day_))) << ", ";
		ss << month_name_long(month_) << " ";
		ss << day_ << " ";


		// TODO Find a better way of implementing this
		std::string commonEraNotation = (year_ > 0) ? "AD" : "BC";
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

	bool is_julian_leapyear(year_t year) { return year % 4 == 0; }
	
	day_t julian_days_in_month(month_t month, bool isLeapYear)
	{
		return civil::days_in_month(month, isLeapYear);
	}
	
	Julian::operator Jd() const {

		return Jd(julian_to_jd(year_, month_, day_, hour_, minute_, second_));

	}

	Julian::operator Gregorian() const{
		return Gregorian(julian_to_jd(*this));
	}
	
	Julian operator - (Julian const& lhs, Julian const& rhs) {

		// TODO Find a better way of doing this using a julian to jd function that takes a julian object as a parameter
		jd_t jd_lhs = julian_to_jd(lhs.year(), lhs.month(), lhs.day(), lhs.hour(), lhs.minute(), lhs.second());
		jd_t jd_rhs = julian_to_jd(rhs.year(), rhs.month(), rhs.day(), rhs.hour(), rhs.minute(), rhs.second());

		return jd_lhs - jd_rhs;

	}
	
	Julian operator + (Julian const& jul, months const& month) {

		year_t y = jul.year() + month.count / 12;
		month_t m = jul.month() + month.count % 12;

		long long adjust = (m - 1) / 12 + (m - 12) / 12;

		y += adjust;
		m -= static_cast<month_t>(adjust * 12);

		day_t d = std::min(jul.day(), gregorian_days_in_month(m, is_julian_leapyear(y)));

		return Julian(y, m, d, jul.hour(), jul.minute(), jul.second());

	}

	Julian operator - (Julian const& jul, months const& months) {

		year_t y = jul.year() - months.count / 12;
		month_t m = jul.month() - months.count % 12;

		int adjust = (m - 1) / 12 - (m - 12) / 12;

		y -= adjust;
		m += adjust * 12;

		day_t d = std::min(jul.day(), gregorian_days_in_month(m, is_julian_leapyear(y)));

		return Julian(y, m, d, jul.hour(), jul.minute(), jul.second());

	}

	Julian operator + (Julian const& jul, years const& years) {

		year_t y = static_cast<year_t>(jul.year() + years.count);
		month_t m = jul.month();
		day_t d = std::min(jul.day(), gregorian_days_in_month(m, is_julian_leapyear(y)));

		return Julian(y, m, d, jul.hour(), jul.minute(), jul.second());
	}

	Julian operator - (Julian const& jul, years const& years) {

		year_t y = static_cast<year_t>(jul.year() - years.count);
		month_t m = jul.month();
		day_t d = std::min(jul.day(), gregorian_days_in_month(m, is_julian_leapyear(y)));

		return Julian(y, m, d, jul.hour(), jul.minute(), jul.second());

	}

	std::ostream& operator << (std::ostream& os, Julian const& jul) {
		return os << jul.to_string();
	}

	


	year_t year(const Julian j) { return j.year(); }

	month_t month(const Julian j) { return j.month(); }

	day_t day(const Julian j) { return j.day(); }

	hour_t hour(const Julian j) { return j.hour(); }

	minute_t minute(const Julian j) { return j.minute(); }

	second_t second(const Julian j) { return j.second(); }
	
}