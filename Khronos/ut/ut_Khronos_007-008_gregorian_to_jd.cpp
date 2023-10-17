/*	ut_Khronos_007-008_gregorian_to_jd.cpp

	Khronos library Gregorian to jdn functions unit test.

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

#include <iomanip>
#include <sstream>
using namespace std;


GATS_TEST_CASE(ut007_gregorian_to_jdn_basic_test, GREGORIAN_CALENDAR_GROUP, 3) {
#if PHASE_7
	using namespace khronos;

	auto test = [this](year_t year, month_t month, day_t day, jd_t jdn, int line) {
		auto jg = gregorian_to_jd(year, month, day);
		ostringstream oss;
		oss << fixed << setprecision(10) << "jg(" << jg << ") != jdn(" << jdn << ") from line: " << line;
		GATS_CHECK_MESSAGE(jg == jdn, oss.str());
	};

	test(4714_BCE, November, 24, -0.5, __LINE__);			// beginning of the Julian Epoch
	test(1_CE, January, 1, GREGORIAN_EPOCH, __LINE__);		// January 1, 1 CE
	test(1582_CE, October, 15, 2'299'160.5, __LINE__);		// Gregorian adoption date Spain, Portugal, Polish-Lithuanian Commonwealth, Papal
	test(1582_CE, December, 20, 2'299'226.5, __LINE__);		// Gregorian adoption date France
	test(1752_CE, September, 14, 2'361'221.5, __LINE__);		// Gregorian adoption date British Empire
	test(1858_CE, November, 16, 2'400'000 - 0.5, __LINE__);
	test(1977_CE, April, 26, 2'443259.5, __LINE__);
	test(2012_CE, September, 14, 2'456'184.5, __LINE__);
	test(2132_CE, August, 31, 2'500'000 - 0.5, __LINE__);
#endif
}



GATS_TEST_CASE(ut008_concept_gregorian_jdn_with_tod_test, GREGORIAN_CALENDAR_GROUP, 7) {
#if PHASE_8
	using namespace khronos;
	auto test = [this](year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t seconds, jd_t jd, int line) {
		auto jg = gregorian_to_jd(year, month, day, hour, minute, seconds);
		ostringstream oss;
		oss << fixed << setprecision(10) << "jg(" << jg << ") != jd(" << jd << ") from line: " << line;
		GATS_CHECK_MESSAGE(jg == jd, oss.str());
	};

	test(2132_CE, August, 31, 12, 0, 0, 2'500'000, __LINE__);
	test(2132_CE, August, 31, 6, 0, 0, 2'500'000 - 0.25, __LINE__);
	test(2132_CE, August, 31, 18, 0, 0, 2'500'000 + 0.25, __LINE__);
	test(2132_CE, August, 31, 12, 0, 1, 2'500'000 + 1.0 / (24 * 60 * 60), __LINE__);
#endif
}
