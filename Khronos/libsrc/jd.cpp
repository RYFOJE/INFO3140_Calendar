/**	@file Jdn.cpp
	@author Garth Santor
	@date 2012-09-16

	Date and time library to_string method implementations.
	*/


#include <khronos/julian_day.hpp>
#include <khronos/gregorian_calendar.hpp>

namespace khronos {

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
			Jd();
		}
	}

	std::string Jd::to_string() const {
		return std::to_string(jd_);
	}

}