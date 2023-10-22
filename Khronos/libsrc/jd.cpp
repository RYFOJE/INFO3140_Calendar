/**	@file Jdn.cpp
	@author Garth Santor
	@date 2012-09-16

	Date and time library to_string method implementations.
	*/


#include <khronos/julian_day.hpp>
#include <format>
#include <khronos/gregorian_calendar.hpp>
#include <khronos/julian_calendar.hpp>

namespace khronos {

	jd_t jd_to_jdn(jd_t jd) {
		return floor(jd + 0.5);
	}

	civil_weekday_codes_long day_of_week(const jd_t jd) {

		return static_cast<civil_weekday_codes_long>(utility::mod((jd + 0.5), 7));

	}
	
	Jd::Jd() : jd_{ 0 }
	{
		time_t utcTime = time(NULL);
		struct tm tmLocal;
		localtime_s(&tmLocal, &utcTime);

		// TODO Find a cleaner solution to this code
		jd_ = gregorian_to_jd(year_t(tmLocal.tm_year) + 1900, month_t(tmLocal.tm_mon + 1),
			day_t(tmLocal.tm_mday), hour_t(tmLocal.tm_hour), minute_t(tmLocal.tm_min), second_t(tmLocal.tm_sec));
	}

	Jd::Jd(now_t now) {
		if (now == NOTIMEOFDAY) {
			// TODO Remove redundant code from 
			time_t utcTime = time(NULL);
			struct tm tmLocal;
			localtime_s(&tmLocal, &utcTime);

			// TODO Find a cleaner solution to this code
			jd_ = gregorian_to_jd(year_t(tmLocal.tm_year) + 1900, month_t(tmLocal.tm_mon + 1), day_t(tmLocal.tm_mday));
		}

		else {
			*this = Jd();
		}
	}

	std::string Jd::to_string() const {
		return "JD " + std::format("{}", jd_);
	}

	std::ostream& operator << (std::ostream& os, Jd const& jd) {
		return os << jd.to_string();
	}

}