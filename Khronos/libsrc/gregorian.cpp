/**	@file	gregorian.cpp
	@author	Garth Santor
	@date	2013-09-19

	Gregorian calendar class implementation.
	*/

#include <khronos/gregorian_calendar.hpp>


namespace khronos {

	//Constructor with JD
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

	// Include if current time of day or not
	// TODO Build this into the default constructor
	Gregorian::Gregorian(now_t isCurrTime) {

		if(isCurrTime == WTIMEOFDAY) Gregorian( Jd(WTIMEOFDAY) );

	}

	jd_t operator - (Gregorian const& lhs, Gregorian const& rhs) {

		jd_t jd_lhs = gregorian_to_jd(lhs);
		jd_t jd_rhs = gregorian_to_jd(rhs);

		return jd_lhs - jd_rhs;
	}

	bool operator == (Gregorian const& lhs, int const& rhs) {

		jd_t jd_lhs = gregorian_to_jd(lhs);

		return jd_lhs == rhs;

	}



}