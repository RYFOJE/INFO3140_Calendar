/*	ut_Khronos_001-003_concepts.cpp

	Khronos concepts testcases

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


GATS_TEST_CASE(ut001_concept_am_pm_UDL, GREGORIAN_CALENDAR_GROUP, 3) {
#if PHASE_1
	using namespace khronos;
	GATS_CHECK_EQUAL(12_am, 0);
	GATS_CHECK_EQUAL(1_am, 1);
	GATS_CHECK_EQUAL(12_pm, 12);
	GATS_CHECK_EQUAL(1_pm, 13);
#endif
}


GATS_TEST_CASE(ut002_concept_time_of_day, GREGORIAN_CALENDAR_GROUP, 3) {
#if PHASE_2
	using namespace khronos;
	GATS_CHECK_EQUAL(SECONDS_PER_DAY, 24 * 60 * 60);
	GATS_CHECK_EQUAL(tod(12_am, 0, 0), 0.0);
	GATS_CHECK_EQUAL(tod(12_pm, 1, 1.5), ((12*60+1)*60+1.5)/SECONDS_PER_DAY);
#endif
}



GATS_TEST_CASE(ut003_concept_CE_BCE_to_Gregorian_astro, GREGORIAN_CALENDAR_GROUP, 3) {
#if PHASE_3
	using namespace khronos;
	GATS_CHECK_EQUAL(1975_CE, 1975);
	GATS_CHECK_EQUAL(1975_BCE, -1974);
#endif
}
