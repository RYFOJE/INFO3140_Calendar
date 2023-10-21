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
		year_t year;
		month_t month;
		day_t day;

		jd_to_gregorian(jd.jd(), year, month, day);
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
		year_(year), month_(month), day_(day), timeOfDay_(tod(hour, minute, second)) {}

	jd_t operator - (Gregorian const& lhs, Gregorian const& rhs) {

		jd_t jd_lhs = gregorian_to_jd(lhs);
		jd_t jd_rhs = gregorian_to_jd(rhs);

		return jd_lhs - jd_rhs;
	}

	bool operator == (Gregorian const& lhs, Gregorian const& rhs) {

		// Faster than converting to jd
		return (lhs.year() == rhs.year() &&
			lhs.month() == rhs.month() &&
			lhs.day() == rhs.day() &&
			lhs.timeOfDay() == rhs.timeOfDay());

	}

	bool operator == (Gregorian const& lhs, int const& rhs) {

		jd_t jd_lhs = gregorian_to_jd(lhs);

		return jd_lhs == rhs;

	}



}