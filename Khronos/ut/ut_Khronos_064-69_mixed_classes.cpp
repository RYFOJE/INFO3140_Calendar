/*	ut_Khronos_064-069_islamic_concepts.cpp

	Khronos library mixed classes unit test.

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



GATS_TEST_CASE(ut064_mixed_differences, MIXED_CALENDAR_GROUP, 1) {
#if PHASE_64
	using namespace khronos;
	Gregorian low(2000);
	Jd high = Jd(low).jd() + 1;
	Julian copyLow(low);

	GATS_CHECK(high - low == 1);
	GATS_CHECK(low - high == -1);
	GATS_CHECK(low - copyLow == 0);
	GATS_CHECK(copyLow - low == 0);
#endif
}



GATS_TEST_CASE(ut065_mixed_relational, MIXED_CALENDAR_GROUP, 1) {
#if PHASE_65
	using namespace khronos;
	Gregorian low(2000);
	Jd high = Jd(low).jd() + 1;
	Julian copyLow(low);

	GATS_CHECK(low == copyLow);
	GATS_CHECK(low < high);
	GATS_CHECK(low <= copyLow);
	GATS_CHECK(high >= low);
	GATS_CHECK(high > low);
	GATS_CHECK(high != low);
#endif
}



/**	Base objects. */
#if PHASE_66 || PHASE_67 || PHASE_68
using namespace khronos;
khronos::Jd const			epochJdn(-0.5);
khronos::Julian const		epochJulian(4713_BC, 1, 1);
khronos::Gregorian const	epochGregorian(4714_BCE, 11, 24);
#endif



/** Test assignment to Jd conversions. */
GATS_TEST_CASE(ut066_assignment_conversion_to_jdn_tests, MIXED_CALENDAR_GROUP, 1) {
#if PHASE_66
	using namespace khronos;

	{	Jd jdn;
	jdn = epochJulian;
	GATS_CHECK(jdn == epochJulian);
	}
	{	Jd jdn;
	jdn = epochGregorian;
	GATS_CHECK(jdn == epochGregorian);
	}
	{	Jd jdn;
	jdn = epochJdn;
	GATS_CHECK(jdn == epochJdn);
	}
#endif
}



/** Test assignment to Gregorian conversions. */
GATS_TEST_CASE(ut067_assignment_conversion_to_gregorian_tests, MIXED_CALENDAR_GROUP, 1) {
#if PHASE_67
	using namespace khronos;
	Gregorian greg;

	{	Gregorian greg;
	greg = epochJulian;
	GATS_CHECK(greg == epochJulian);
	}
	{	Gregorian greg;
	greg = epochGregorian;
	GATS_CHECK(greg == epochGregorian);
	}
	{	Gregorian greg;
	greg = epochJdn;
	GATS_CHECK(greg == epochJdn);
	}
#endif
}



/** Test assignment to Julian conversions. */
GATS_TEST_CASE(ut068_assignment_conversion_to_julian_tests, MIXED_CALENDAR_GROUP, 1) {
#if PHASE_68
	using namespace khronos;

	Julian julian;

	{	Julian julian;
	julian = epochJulian;
	GATS_CHECK(julian == epochJulian);
	}
	{	Julian julian;
	julian = epochGregorian;
	GATS_CHECK(julian == epochGregorian);
	}
	{	Julian julian;
	julian = epochJdn;
	GATS_CHECK(julian == epochJdn);
	}
#endif
}



/** Test now */
GATS_TEST_CASE(ut069_test_defaults, MIXED_CALENDAR_GROUP, 1) {
#if PHASE_69
	using namespace khronos;

	Gregorian gNow(NOTIMEOFDAY);
	Julian jNow(NOTIMEOFDAY);
	Islamic iNow(NOTIMEOFDAY);
	Hebrew hNow(NOTIMEOFDAY);
	Jd now(NOTIMEOFDAY);

	GATS_CHECK(gNow == jNow);
	GATS_CHECK(iNow == hNow);
#endif
}
