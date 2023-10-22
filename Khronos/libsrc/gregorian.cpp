/**	@file	gregorian.cpp
	@author	Garth Santor
	@date	2013-09-19

	Gregorian calendar class implementation.
	*/

#include <khronos/gregorian_calendar.hpp>
#include <iomanip>


namespace khronos {

	jd_t gregorian_to_jd(const Gregorian g) {
		return gregorian_to_jd(g.year(), g.month(), g.day(), g.hour(), g.minute(), g.second());
	}

	Gregorian::Gregorian(jd_t jd) {
		jd_to_gregorian(jd, year_, month_, day_, hour_, minute_, second_);

	}

	Gregorian::Gregorian(Jd const& jd) {
		jd_to_gregorian(jd.jd(), year_, month_, day_, hour_, minute_, second_);
	}

	Gregorian::Gregorian(now_t isCurrTime) {

		// TODO Remove redundant code from 
		time_t utcTime = time(NULL);
		struct tm tmLocal;
		localtime_s(&tmLocal, &utcTime);

		if (isCurrTime == NOTIMEOFDAY) {
			// TODO Find better way than using pointer as it will initialize two classes
			*this = Gregorian(tmLocal.tm_year + 1900, tmLocal.tm_mon + 1, tmLocal.tm_mday);
		}

		else {
			// TODO Find better way than using pointer as it will initialize two classes
			*this = Gregorian(tmLocal.tm_year + 1900, tmLocal.tm_mon + 1,
				tmLocal.tm_mday, tmLocal.tm_hour, tmLocal.tm_min, tmLocal.tm_sec);
		}

	}

	Gregorian::Gregorian(year_t year, month_t month, day_t day,
		hour_t hour, minute_t minute, second_t second) :
		year_(year), month_(month), day_(day), 
		hour_(hour), minute_(minute), second_(second) {}


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



	jd_t operator - (Gregorian const& lhs, Gregorian const& rhs) {

		jd_t jd_lhs = gregorian_to_jd(lhs);
		jd_t jd_rhs = gregorian_to_jd(rhs);

		return jd_lhs - jd_rhs;
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
		year_t year = lhs.year() + rhs.count;
		month_t month = lhs.month();
		day_t day = (month == 2 && lhs.day() == 29 && !is_gregorian_leapyear(year)) ? 28 : lhs.day();
		
		return Gregorian(year, month, day, lhs.hour(), lhs.minute(), lhs.second());
	}

	Gregorian operator - (Gregorian const& lhs, years const& rhs) {
		year_t year = lhs.year() - rhs.count;
		month_t month = lhs.month();
		day_t day = (month == 2 && lhs.day() == 28 && !is_gregorian_leapyear(year)) ? 28 : lhs.day();

		return Gregorian(year, month, day, lhs.hour(), lhs.minute(), lhs.second());
	}
	
	Gregorian::operator Jd() const {
		
		return Jd(gregorian_to_jd(year_, month_, day_, hour_, minute_, second_));

	}
	

	year_t year(const Gregorian g) { return g.year(); }

	month_t month(const Gregorian g) { return g.month(); }

	day_t day(const Gregorian g) { return g.day(); }

	hour_t hour(const Gregorian g) { return g.hour(); }

	minute_t minute(const Gregorian g) { return g.minute(); }

	second_t second(const Gregorian g) { return g.second(); }

}