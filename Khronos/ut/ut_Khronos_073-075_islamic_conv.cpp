/*	ut_khronos_073-075_islamic_conv.cpp

	Khronos library Islamic Calendar conversions unit test.

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
using namespace std;



/** Test known Islamic to JDN conversions. */
GATS_TEST_CASE(ut073_test_islamic_to_jd, ISLAMIC_CALENDAR_GROUP,2) {
#if PHASE_73
	using namespace khronos;

	auto test = [this](year_t year, month_t month, day_t day, jd_t jdn)->bool {
		return islamic_to_jd(year, month, day) == jdn;
	};

	GATS_CHECK(test(-5498, Shaban, 16, -0.5));			// beginning of the Julian Epoch
	GATS_CHECK(test(1, Muharram, 1, ISLAMIC_EPOCH));	// Muharram 1, 1 A.H.
	GATS_CHECK(test(990, Ramadan, 17, 2'299'160.5));		// Gregorian adoption date Spain, Portugal, Polish-Lithuanian Commonwealth, Papal
	GATS_CHECK(test(990, DhulQadah, 24, 2'299'226.5));		// Gregorian adoption date France
	GATS_CHECK(test(1165, DhulQadah, 5, 2'361'221.5));		// Gregorian adoption date British Empire
	GATS_CHECK(test(1275, RabiathThani, 9, 2'400'000 - 0.5));
	GATS_CHECK(test(1433, Shawwal, 27, 2'456'184.5));
	GATS_CHECK(test(1557, JumadatTania, 18, 2'500'000 - 0.5));


	auto test2 = [this](year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t seconds, jd_t jdn) {
		auto jd = islamic_to_jd(year, month, day, hour, minute, seconds);
		GATS_CHECK_EQUAL(jd, jdn);
	};
	test2(1557, JumadatTania, 19, 12, 0, 0, 2'500'000);
	test2(1557, JumadatTania, 18, 6, 0, 0, 2'500'000 - 0.25);
	test2(1557, JumadatTania, 19, 18, 0, 0, 2'500'000 + 0.25);
	test2(1557, JumadatTania, 19, 12, 0, 1, 2'500'000 + 1.0 / (24 * 60 * 60));
#endif
}



/**	Test known JDN to Islamic conversions. */
GATS_TEST_CASE(ut074_test_jd_to_islamic, ISLAMIC_CALENDAR_GROUP,2) {
#if PHASE_74
	using namespace khronos;

	auto test = [this](year_t year, month_t month, day_t day, jd_t jd)->bool {
		year_t y;
		month_t m;
		day_t d;
		jd_to_islamic(jd, y, m, d);
		return y == year && m == month && d == day;
	};

	GATS_CHECK(test(-5498, Shaban, 16, -0.5));				// beginning of the Julian Epoch
	GATS_CHECK(test(1, Muharram, 1, ISLAMIC_EPOCH));		// January 1, 1 CE
	GATS_CHECK(test(990, Ramadan, 17, 2'299'160.5));			// Gregorian adoption date Spain, Portugal, Polish-Lithuanian Commonwealth, Papal
	GATS_CHECK(test(990, DhulQadah, 24, 2'299'226.5));		// Gregorian adoption date France
	GATS_CHECK(test(1165, DhulQadah, 5, 2'361'221.5));		// Gregorian adoption date British Empire
	GATS_CHECK(test(1275, RabiathThani, 9, 2'400'000 - 0.5));
	GATS_CHECK(test(1433, Shawwal, 27, 2'456'184.5));
	GATS_CHECK(test(1557, JumadatTania, 18, 2'500'000 - 0.5));


	auto test2 = [this](year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t seconds, jd_t jd) {
		year_t y;
		month_t m;
		day_t d;
		hour_t h;
		minute_t mi;
		second_t s;
		jd_to_islamic(jd, y, m, d, h, mi, s);
		GATS_CHECK_EQUAL(y, year);
		GATS_CHECK_EQUAL(m, month);
		GATS_CHECK_EQUAL(d, day);
		GATS_CHECK_EQUAL(h, hour);
		GATS_CHECK_EQUAL(mi, minute);
		GATS_CHECK_EQUAL(s, seconds);
	};
	test2(1557, JumadatTania, 19, 12, 0, 0, 2'500'000);
	test2(1557, JumadatTania, 18, 6, 0, 0, 2'500'000 - 0.25);
	test2(1557, JumadatTania, 19, 18, 0, 0, 2'500'000 + 0.25);
	test2(1557, JumadatTania, 19, 12, 0, 1, 2'500'000 + 1.0 / (24 * 60 * 60));
#endif
}



/**	Check all conversions from the lowest Proleptic Islamic date, until a day well in the future. */
GATS_TEST_CASE(ut075_test_islamic_full, ISLAMIC_CALENDAR_GROUP,1) {
#if PHASE_75
	using namespace khronos;
	cout << "Starting Islamic FULL_TEST: ";
	jd_t low = islamic_to_jd(-4799, 1, 1);
	jd_t high = islamic_to_jd(4800, 1, 1);
	for (jd_t jdn = low; jdn <= high; jdn += 1.0) {
		year_t year;
		month_t month;
		day_t day;
		jd_to_islamic(jdn, year, month, day);
		jd_t result = islamic_to_jd(year, month, day);
		GATS_CHECK_EQUAL(jdn, result);
	}
	cout << "... completed\n";
#endif
}
