/*	ut_Khronos_090-092_hebrew_conv.cpp

	Khronos library Hebrew Calendar conversion unit test.

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.09.25
	Replaced BOOST's test framework with gats_test framework.

Version 2016.09.30
	Added: Phase List

Version 2015.09.21
	Initial Release


=============================================================

Copyright Garth Santor/Trinh Han

The copyright to the computer program(s) herein
is the property of Garth Santor/Trinh Han, Canada.
The program(s) may be used and/or copied only with
the written permission of Garth Santor/Trinh Han
or in accordance with the terms and conditions
stipulated in the agreement/contract under which
the program(s) have been supplied.
=============================================================*/

#include <khronos.hpp>
#include "ut_Khronos.hpp"
#include <random>
#include <functional>
#include <chrono>
using namespace std;



/** Test known Hebrew to JD conversions. */
GATS_TEST_CASE(ut090_test_hebrew_to_jd, HEBREW_CALENDAR_GROUP, 1) {
#if PHASE_90
	using namespace khronos;

	auto test = [](year_t year, month_t month, day_t day, jd_t jd)->bool {
		return hebrew_to_jd(year, month, day) == jd;
	};

	GATS_CHECK(test(-952, Teveth, 20, -0.5));				// beginning of the Julian Epoch
	GATS_CHECK(test(1, Nisan, 1, 348'175.5));			// January 1, 1
	GATS_CHECK(test(5343, Tishri, 19, 2'299'160.5));			// Gregorian adoption date Spain, Portugal, Polish-Lithuanian Commonwealth, Papal
	GATS_CHECK(test(5343, Kislev, 25, 2'299'226.5));			// Gregorian adoption date France
	GATS_CHECK(test(5513, Tishri, 6, 2'361'221.5));		// Gregorian adoption date British Empire
	GATS_CHECK(test(5619, Kislev, 9, 2'400'000 - 0.5));
	GATS_CHECK(test(5772, Elul, 27, 2'456'184.5));
	GATS_CHECK(test(5892, Elul, 19, 2'500'000 - 0.5));


	auto test2 = [this](year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t seconds, jd_t jd) {
		auto result = hebrew_to_jd(year, month, day, hour, minute, seconds);
		GATS_CHECK_EQUAL(result, jd);
	};
	test2(5892, Elul, 20, 12, 0, 0, 2'500'000);
	test2(5892, Elul, 19, 6, 0, 0, 2'500'000 - 0.25);
	test2(5892, Elul, 20, 18, 0, 0, 2'500'000 + 0.25);
	test2(5892, Elul, 20, 12, 0, 1, 2'500'000 + 1.0 / (24 * 60 * 60));
#endif
}



/**	Test known JD to Hebrew conversions. */
GATS_TEST_CASE(ut091_test_jd_to_hebrew, HEBREW_CALENDAR_GROUP, 1) {
#if PHASE_91
	using namespace khronos;

	auto test = [](year_t year, month_t month, day_t day, jd_t jd)->bool {
		year_t y;
		month_t m;
		day_t d;
		jd_to_hebrew(jd, y, m, d);
		return y == year && m == month && d == day;
	};

	GATS_CHECK(test(-952, Teveth, 20, -0.5));				// beginning of the Julian Epoch
	GATS_CHECK(test(1, Nisan, 1, 348'175.5));			// January 1, 1
	GATS_CHECK(test(5343, Tishri, 19, 2'299'160.5));			// Gregorian adoption date Spain, Portugal, Polish-Lithuanian Commonwealth, Papal
	GATS_CHECK(test(5343, Kislev, 25, 2'299'226.5));			// Gregorian adoption date France
	GATS_CHECK(test(5513, Tishri, 6, 2'361'221.5));		// Gregorian adoption date British Empire
	GATS_CHECK(test(5619, Kislev, 9, 2'400'000 - 0.5));
	GATS_CHECK(test(5772, Elul, 27, 2'456'184.5));
	GATS_CHECK(test(5892, Elul, 19, 2'500'000 - 0.5));


	auto test2 = [this](year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t seconds, jd_t jd) {
		year_t y;
		month_t m;
		day_t d;
		hour_t h;
		minute_t mi;
		second_t s;
		jd_to_hebrew(jd, y, m, d, h, mi, s);
		GATS_CHECK_EQUAL(y, year);
		GATS_CHECK_EQUAL(m, month);
		GATS_CHECK_EQUAL(d, day);
		GATS_CHECK_EQUAL(h, hour);
		GATS_CHECK_EQUAL(mi, minute);
		GATS_CHECK_EQUAL(s, seconds);
	};
	auto start = 2'499'999.5;
	test2(5892, Elul, 19, 0, 0, 0, start);
	test2(5892, Elul, 19, 6, 0, 0, start + 0.25);
	test2(5892, Elul, 20, 12, 0, 0, start + 0.5);
	test2(5892, Elul, 20, 12, 0, 1, start + 0.5 + 1.0 / (24 * 60 * 60));
#endif
}



/**	Check all conversions from the lowest Proleptic Gregorian date, until a day well in the future. */
GATS_TEST_CASE(ut092_test_hebrew_full, HEBREW_CALENDAR_GROUP, 1) {
#if PHASE_92
	using namespace khronos;

	cout << "Starting Hebrew FULL_TEST: ";
	static default_random_engine dr;

	static uniform_int_distribution<int> yearDist(-2000, 10'000);
	static auto yearGen = bind(yearDist, dr);
	for (auto iY = 0; iY < 20; ++iY) {
		year_t year = yearGen();
		uniform_int_distribution<int> monthDist(1, hebrew_months_in_year(year));
		auto monthGen = bind(monthDist, dr);
		for (auto iMon = 0; iMon < 10; ++iMon) {
			month_t month = (month_t)monthGen();
			uniform_int_distribution<int> dayDist(1, hebrew_days_in_month(year, month));
			auto dayGen = bind(dayDist, dr);
			for (auto iDay = 0; iDay < 10; ++iDay) {
				day_t day = (day_t)dayGen();
				static uniform_int_distribution<int> hourDist(0, 23);
				static auto hourGen = bind(hourDist, dr);
				for (auto iH = 0; iH < 10; ++iH) {
					hour_t hour = (hour_t)hourGen();
					static uniform_int_distribution<int> minSecDist(0, 59);
					static auto minSecGen = bind(minSecDist, dr);
					for (auto iMin = 0; iMin < 10; ++iMin) {
						minute_t minute = (minute_t)minSecGen();
						for (auto iSec = 0; iSec < 10; ++iSec) {
							second_t second = (second_t)minSecGen();

							jd_t jd = hebrew_to_jd(year, month, day);
							year_t ye;
							month_t mo;
							day_t da;
							jd_to_hebrew(jd, ye, mo, da);
							GATS_CHECK_EQUAL(year, ye);
							GATS_CHECK_EQUAL(month, mo);
							GATS_CHECK_EQUAL(day, da);

							jd = hebrew_to_jd(year, month, day, hour, minute, second);
							hour_t ho;
							minute_t mi;
							second_t se;
							jd_to_hebrew(jd, ye, mo, da, ho, mi, se);
							GATS_CHECK_EQUAL(year, ye);
							GATS_CHECK_EQUAL(month, mo);
							GATS_CHECK_EQUAL(day, da);
							GATS_CHECK_EQUAL(hour, ho);
							GATS_CHECK_EQUAL(minute, mi);
							GATS_CHECK_EQUAL(second, se);
						}
					}
				}
			}
		}
	}
	cout << "... completed\n";
#endif
}
