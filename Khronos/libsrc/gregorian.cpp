/**	@file	gregorian.cpp
	@author	Garth Santor
	@date	2013-09-19

	Gregorian calendar class implementation.
	*/

#include <khronos/gregorian_calendar.hpp>


namespace khronos {

	Gregorian::Gregorian(jd_t jd) {
		year_t year;
		month_t month;
		day_t day;

		jd_to_gregorian(jd, year, month, day);

		Gregorian(year, month, day);

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
		
		hour_t hour = lhs.hour();
		minute_t minute = lhs.minute();
		second_t second = lhs.second();
		
		return Gregorian(year, month, day, hour, minute, second);
		
	}
	
	Gregorian operator - (Gregorian const& lhs, months const& rhs) {

		year_t year = lhs.year() - rhs.count / 12;
		month_t month = lhs.month() - rhs.count % 12;
		int adjust = (month - 1) / 12 - (month - 12) / 12;
		year -= adjust;
		month += adjust * 12;
		day_t day = std::min(lhs.day(), gregorian_days_in_month(month, is_gregorian_leapyear(year)));

		hour_t hour = lhs.hour();
		minute_t minute = lhs.minute();
		second_t second = lhs.second();

		return Gregorian(year, month, day, hour, minute, second);
		
	}
	
	Gregorian::operator Jd() const {
		
		return Jd(gregorian_to_jd(year_, month_, day_, hour_, minute_, second_));

	}
	
}