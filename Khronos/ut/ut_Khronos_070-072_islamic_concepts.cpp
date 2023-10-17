/*	ut_Khronos_070-072_islamic_concepts.cpp

	Khronos library Islamic Calendar concepts unit test.

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
#include <array>
using namespace std;

constexpr double oneThird = 1.0 / 3.0;



GATS_TEST_CASE(ut070_test_Islamic_leapyear_test, ISLAMIC_CALENDAR_GROUP, oneThird) {
#if PHASE_70
	using namespace khronos;
	GATS_CHECK_EQUAL(is_islamic_leapyear(1400), false);
	GATS_CHECK_EQUAL(is_islamic_leapyear(1401), true);
	GATS_CHECK_EQUAL(is_islamic_leapyear(1402), false);
	GATS_CHECK_EQUAL(is_islamic_leapyear(1403), false);
	GATS_CHECK_EQUAL(is_islamic_leapyear(1404), true);
	GATS_CHECK_EQUAL(is_islamic_leapyear(1405), false);
	GATS_CHECK_EQUAL(is_islamic_leapyear(0), false);
	GATS_CHECK_EQUAL(is_islamic_leapyear(-1), true);
#endif
}



/** Check islamic leap years. */
GATS_TEST_CASE(ut071_test_islamic_leapyear, ISLAMIC_CALENDAR_GROUP, oneThird) {
#if PHASE_71
	using namespace khronos;
	GATS_CHECK_EQUAL(is_islamic_leapyear(-5498), true);				// beginning of the Julian Epoch
	GATS_CHECK_EQUAL(is_islamic_leapyear(1), false);				// Muharram 1, 1 A.H.
	GATS_CHECK_EQUAL(is_islamic_leapyear(990), false);				// Gregorian adoption date Spain, Portugal, Polish-Lithuanian Commonwealth, Papal
	GATS_CHECK_EQUAL(is_islamic_leapyear(1165), false);				// Gregorian adoption date British Empire
	GATS_CHECK_EQUAL(is_islamic_leapyear(1275), false);
	GATS_CHECK_EQUAL(is_islamic_leapyear(1433), false);
	GATS_CHECK_EQUAL(is_islamic_leapyear(1434), true);
	GATS_CHECK_EQUAL(is_islamic_leapyear(1557), false);
#endif
}



GATS_TEST_CASE(ut072_test_Islamic_month_name, ISLAMIC_CALENDAR_GROUP, oneThird) {
#if PHASE_72
	using namespace khronos;
	std::array<std::string, 13> const names = { "", "Muharram", "Safar", "Rabi'al-Awwal",
		"Rabi'ath-Thani", "Jumada I-Ula", "Jumada t-Tania", "Rajab", "Sha'ban", "Ramadan", "Shawwal",
		"Dhu I-Qa'da", "Dhu I-Hijja" };

	for (month_t i = 1; i <= 12; ++i)
		GATS_CHECK(islamic_month_name(i) == names[i]);
#endif
}
