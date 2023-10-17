/*	ut_Khronos_108-114_vulcan_class.cpp

	Khronos library Vulcan Calendar class unit test.

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
#include <ctime>
using namespace std;

#include "ut_utilities.hpp"

constexpr double oneSixth = 1.0 / 6.0;


/* Default constructor initializes to current time. */
GATS_TEST_CASE(ut108_test_Vulcan_ctor_default, VULCAN_CALENDAR_GROUP, oneSixth) {
#if PHASE_108
	using namespace khronos;
	time_t utcTime = time(NULL);
	Vulcan const	now;
	struct tm tmLocal;
	localtime_s(&tmLocal, &utcTime);

	Gregorian		localDateTime(
		year_t(tmLocal.tm_year) + 1900,
		month_t(tmLocal.tm_mon + 1),
		day_t(tmLocal.tm_mday),
		hour_t(tmLocal.tm_hour),
		minute_t(tmLocal.tm_min),
		second_t(tmLocal.tm_sec)
		);

	auto v = ((Jd)now).jd();
	auto g = ((Jd)localDateTime).jd();

	GATS_CHECK_WITHIN(v, g, 0.000'01);
#endif
}



GATS_TEST_CASE(ut109_test_Vulcan_ctor_literal, VULCAN_CALENDAR_GROUP, oneSixth) {
#if PHASE_109
	using namespace khronos;
	Vulcan const epochVulcan(-4712, Zat, 1);
	GATS_CHECK(-4712 == epochVulcan.year());
	GATS_CHECK(January == epochVulcan.month());
	GATS_CHECK(1 == epochVulcan.day());

	Vulcan const greatWar(1918, October, 29, 11, 11, 11);
	GATS_CHECK(1918 == greatWar.year());
	GATS_CHECK(October == greatWar.month());
	GATS_CHECK(29 == greatWar.day());
	GATS_CHECK(11 == greatWar.hour());
	GATS_CHECK(11 == greatWar.minute());
	GATS_CHECK(11 == greatWar.second());
#endif
}



GATS_TEST_CASE(ut110_test_Vulcan_ctor_from_Jd, VULCAN_CALENDAR_GROUP, oneSixth) {
#if PHASE_110
	using namespace khronos;
	Jd jd = VULCAN_EPOCH;
	Vulcan v(jd);
	GATS_CHECK_EQUAL(v.year(), 1);
	GATS_CHECK_EQUAL(v.month(), Zat);
	GATS_CHECK_EQUAL(v.day(), 1);
	GATS_CHECK_EQUAL(v.hour(), 0);
	GATS_CHECK_EQUAL(v.minute(), 0);
	GATS_CHECK_EQUAL(v.second(), 0);
#endif
}



GATS_TEST_CASE(ut111_test_Vulcan_cast_to_Jd, VULCAN_CALENDAR_GROUP, oneSixth) {
#if PHASE_111
	using namespace khronos;
	Vulcan const	vulcanEpoch(1, Zat, 1);
	Jd je = vulcanEpoch;
	GATS_CHECK_EQUAL(je.jd(), VULCAN_EPOCH);
#endif
}



GATS_TEST_CASE(ut112_test_Vulcan_assignment_from_Jd, VULCAN_CALENDAR_GROUP, oneSixth) {
#if PHASE_112
	using namespace khronos;
	Vulcan g;
	g = Jd(VULCAN_EPOCH);
	GATS_CHECK_EQUAL(g.year(), 1);
	GATS_CHECK_EQUAL(g.month(), Zat);
	GATS_CHECK_EQUAL(g.day(), 1);
	GATS_CHECK_EQUAL(g.hour(), 0);
	GATS_CHECK_EQUAL(g.minute(), 0);
	GATS_CHECK_EQUAL(g.second(), 0);
#endif
}



GATS_TEST_CASE(ut113_test_Vulcan_add_days, VULCAN_CALENDAR_GROUP, oneSixth) {
#if PHASE_113
	using namespace khronos;
	Vulcan d(1, Zat, 1);
	Vulcan res = d + days(10);
	GATS_CHECK(res == Vulcan(1, Zat, 11));
	res = res - days(10);
	GATS_CHECK(res == d);
#endif
}



GATS_TEST_CASE(ut114_test_Vulcan_add_days_with_time, VULCAN_CALENDAR_GROUP, oneSixth) {
#if PHASE_114
	using namespace khronos;
	Vulcan d(2000, January, 1, 12, 13, 14);
	Vulcan res = d + days(10);
	GATS_CHECK(res == Vulcan(2000, January, 11, 12, 13, 14));
	res = res - days(10);
	GATS_CHECK(res == d);
#endif
}



GATS_TEST_CASE(ut115_test_Vulcan_add_months, VULCAN_CALENDAR_GROUP, oneSixth) {
#if PHASE_115
	using namespace khronos;
	{	Vulcan start(2000, JAN, 1);
	Vulcan end(2000, FEB, 1);
	Vulcan res = start + months(1);
	GATS_CHECK(end == res);
	res = end - months(1);
	GATS_CHECK(res == start);
	}
	{	Vulcan start(2000, JAN, 1, 12, 13, 14);
	Vulcan end(2001, FEB, 1, 12, 13, 14);
	Vulcan res = start + months(13);
	GATS_CHECK(end == res);
	res = end - months(13);
	GATS_CHECK(res == start);
	}

	// shouldn't compile
	//start + months(1.2);
#endif
}



GATS_TEST_CASE(ut116_test_Vulcan_add_years, VULCAN_CALENDAR_GROUP, oneSixth) {
#if PHASE_116
	using namespace khronos;
	Vulcan date(2000, January, 1);
	Vulcan result = date + years(10);
	GATS_CHECK(Vulcan(2010, January, 1) == result);
	result = result - years(10);
	GATS_CHECK(result == date);

	// The following won't compile (we made the operator private)
	//result = date + years(10.4);
#endif
}



GATS_TEST_CASE(ut117_test_Vulcan_relational, VULCAN_CALENDAR_GROUP, oneSixth) {
#if PHASE_117
	using namespace khronos;
	Vulcan low(2009, 1, 1);
	Vulcan high(2009, 12, 31);
	Vulcan copyLow(low);

	GATS_CHECK(low == copyLow);
	GATS_CHECK(low < high);
	GATS_CHECK(low <= copyLow);
	GATS_CHECK(high >= low);
	GATS_CHECK(high > low);
	GATS_CHECK(high != low);
#endif
}



GATS_TEST_CASE(ut118_test_Vulcan_to_string, VULCAN_CALENDAR_GROUP, oneSixth) {
#if PHASE_118
	using namespace khronos;
	GATS_CHECK_EQUAL(Vulcan(1000, Zat, 1).to_string(), std::string("Z'at 1, 1000 0:00:00"));
	GATS_CHECK_EQUAL(Vulcan(2000, reTKhutai, 21, 12, 30, 11).to_string(), std::string("re'T'Khutai 21, 2000 12:30:11"));
	GATS_CHECK_EQUAL(Vulcan(2010, Tlakht, 12, 17, 45, 8).to_string(), std::string("T'lakht 12, 2010 17:45:08"));
	GATS_CHECK_EQUAL(Vulcan(-100, Tasmeen, 1, 6, 7, 8).to_string(), std::string("Tasmeen 1, -100 6:07:08"));

	std::ostringstream oss;
	oss << Vulcan(2010, TaKrat, 12, 11, 45, 8);
	GATS_CHECK_EQUAL(oss.str(), std::string("Ta'Krat 12, 2010 11:45:08"));
#endif
}



GATS_TEST_CASE(ut119_test_Vulcan_element_functions, VULCAN_CALENDAR_GROUP, oneSixth) {
#if PHASE_119
	using namespace khronos;
	Vulcan g(2010, Tasmeen, 12, 23, 45, 8);
	GATS_CHECK_EQUAL(year(g), 2010);
	GATS_CHECK_EQUAL(month(g), Tasmeen);
	GATS_CHECK_EQUAL(day(g), 12);
	GATS_CHECK_EQUAL(hour(g), 23);
	GATS_CHECK_EQUAL(minute(g), 45);
	GATS_CHECK_EQUAL(second(g), 8);
#endif
}
