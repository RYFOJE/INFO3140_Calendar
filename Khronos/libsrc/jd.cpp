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

	void jd_to_gregorian(jd_t jd, year_t& year, month_t& month, day_t& day) {

		// TOD Add better handling for Gregorian_Epoch
		if (jd == GREGORIAN_EPOCH) {
			year = 1;
			month = 1;
			day = 1;
			return;
		}

		jd = floor(jd - 0.5) + 0.5;
		long long j = static_cast<long long>(jd + 0.5) + 32044;
		long long g = j / 146097;
		long long dg = j % 146097;
		long long c = (dg / 36524 + 1) * 3 / 4;
		long long dc = dg - c * 36524;
		long long b = dc / 1461;
		long long db = dc % 1461;
		long long a = (db / 365 + 1) * 3 / 4;
		long long da = db - a * 365;
		long long y = g * 400 + c * 100 + b * 4 + a;
		long long m = (da * 5 + 308) / 153 - 2;
		year = y - 4800 + (m + 2) / 12;
		month = (m + 2) % 12 + 1;
		day = static_cast<day_t>(da - (m + 4) * 153 / 5 + 123);
	}

	void jd_to_gregorian(jd_t jd, year_t& year, month_t& month, day_t& day,
		hour_t& hours, minute_t& minutes, second_t& seconds) {

		jd_to_gregorian(jd, year, month, day);

		// TODO Better implementation of the modulo
		tod_to_hms(utility::mod(jd, 1), hours, minutes, seconds);

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