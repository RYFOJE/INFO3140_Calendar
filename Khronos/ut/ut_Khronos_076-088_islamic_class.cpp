/*	ut_Khronos_076-088_islamic_class.cpp

	Khronos library Islamic Calendar class unit test.

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

constexpr double oneThirteenth = 1.0 / 13.0;


/* Default constructor initializes to current time. */
GATS_TEST_CASE(ut076_Islamic_ctor_default, ISLAMIC_CALENDAR_GROUP, oneThirteenth) {
#if PHASE_76
	using namespace khronos;
	time_t utcTime = time(NULL);
	Islamic const now;
	Islamic const today(NOTIMEOFDAY);
	struct tm tmLocal;
	localtime_s(&tmLocal, &utcTime);

	Gregorian localDateTime(
		year_t(tmLocal.tm_year) + 1900,
		month_t(tmLocal.tm_mon) + 1,
		day_t(tmLocal.tm_mday),
		hour_t(tmLocal.tm_hour),
		minute_t(tmLocal.tm_min),
		second_t(tmLocal.tm_sec)
		);

	Gregorian localDate(
		year_t(tmLocal.tm_year) + 1900,
		month_t(tmLocal.tm_mon) + 1,
		day_t(tmLocal.tm_mday)
		);

	GATS_CHECK(localDateTime == now);
	GATS_CHECK(localDate == today);
#endif
}



GATS_TEST_CASE(ut077_test_Islamic_ctor_literal, ISLAMIC_CALENDAR_GROUP, oneThirteenth) {
#if PHASE_77
	using namespace khronos;
	Islamic const	islamicEpoch(1, Muharram, 1);
	GATS_CHECK(1 == islamicEpoch.year());
	GATS_CHECK(Muharram == islamicEpoch.month());
	GATS_CHECK(1 == islamicEpoch.day());

	Islamic const aDay(1434, DhulHijja, 1, 12, 30, 45);
	GATS_CHECK(1434 == aDay.year());
	GATS_CHECK(DhulHijja == aDay.month());
	GATS_CHECK(1 == aDay.day());
	GATS_CHECK(12 == aDay.hour());
	GATS_CHECK(30 == aDay.minute());
	GATS_CHECK(45 == aDay.second());
#endif
}



GATS_TEST_CASE(ut078_test_Islamic_ctor_from_Jd, ISLAMIC_CALENDAR_GROUP, oneThirteenth) {
#if PHASE_78
	using namespace khronos;
	Islamic i(Jd(0.0));
	GATS_CHECK_EQUAL(i.year(), -5498);
	GATS_CHECK_EQUAL(i.month(), Shaban);
	GATS_CHECK_EQUAL(i.day(), 17);
	GATS_CHECK_EQUAL(i.hour(), 12);
	GATS_CHECK_EQUAL(i.minute(), 0);
	GATS_CHECK_EQUAL(i.second(), 0);
#endif
}



GATS_TEST_CASE(ut079_test_Islamic_cast_to_Jd, ISLAMIC_CALENDAR_GROUP, oneThirteenth) {
#if PHASE_79
	using namespace khronos;
	Islamic const	i(-5498, Shaban, 17, 12, 0, 0);
	Jd je = i;
	GATS_CHECK_EQUAL(je.jd(), 0.0);
#endif
}



GATS_TEST_CASE(ut080_test_Islamic_assignment_from_Jd, ISLAMIC_CALENDAR_GROUP, oneThirteenth) {
#if PHASE_80
	using namespace khronos;
	Islamic i;
	i = Jd(0.0);
	GATS_CHECK_EQUAL(i.year(), -5498);
	GATS_CHECK_EQUAL(i.month(), Shaban);
	GATS_CHECK_EQUAL(i.day(), 17);
	GATS_CHECK_EQUAL(i.hour(), 12);
	GATS_CHECK_EQUAL(i.minute(), 0);
	GATS_CHECK_EQUAL(i.second(), 0);
#endif
}



GATS_TEST_CASE(ut081_test_Islamic_add_days, ISLAMIC_CALENDAR_GROUP, oneThirteenth) {
#if PHASE_81
	using namespace khronos;
	Islamic date(1434, DhulHijja, 17);
	Islamic res = date + days(100);
	GATS_CHECK(res == Islamic(1435, RabialAwwal, 28));
	res = res - days(100);
	GATS_CHECK(res == date);
#endif
}



GATS_TEST_CASE(ut082_test_Islamic_add_weeks, ISLAMIC_CALENDAR_GROUP, oneThirteenth) {
#if PHASE_82
	using namespace khronos;
	Islamic date(1400, Muharram, 1);
	Islamic res = date + weeks(10);
	GATS_CHECK(date + days(70) == res);
	res = res - weeks(10);
	GATS_CHECK(date == res);
#endif
}



GATS_TEST_CASE(ut083_test_Islamic_add_months, ISLAMIC_CALENDAR_GROUP, oneThirteenth) {
#if PHASE_83
	using namespace khronos;
	Islamic start(1400, Muharram, 1);
	{
		Islamic end(1400, Safar, 1);
		Islamic res = start + months(1);
		GATS_CHECK(end == res);
		res = end - months(1);
		GATS_CHECK(res == start);
	}
	{	Islamic end(1401, Safar, 1);
	Islamic res = start + months(13);
	GATS_CHECK_EQUAL(end, res);
	res = end - months(13);
	GATS_CHECK_EQUAL(res, start);
	}

	// shouldn't compile
	// start + months(1.2);
#endif
}



GATS_TEST_CASE(ut084_test_Islamic_add_month_leap, ISLAMIC_CALENDAR_GROUP, oneThirteenth) {
#if PHASE_84
	using namespace khronos;

	{	Islamic start(1401, Muharram, 30);
	Islamic forward(1401, Safar, 29);
	Islamic back(1401, Muharram, 29);

	auto result = start + months(1);
	GATS_CHECK(result == forward);
	result = forward - months(1);
	GATS_CHECK(result == back);
	}

	{	Islamic start(1434, DhulQadah, 30, 6, 7, 8);
	Islamic forward(1434, DhulHijja, 30, 6, 7, 8);
	Islamic back(1434, DhulQadah, 30, 6, 7, 8);

	auto result = start + months(1);
	GATS_CHECK(result == forward);
	result = forward - months(1);
	GATS_CHECK(result == back);
	}

	{	Islamic start(1435, DhulQadah, 30, 12, 13, 14);
	Islamic forward(1435, DhulHijja, 29, 12, 13, 14);
	Islamic back(1435, DhulQadah, 29, 12, 13, 14);

	auto result = start + months(1);
	GATS_CHECK(result == forward);
	result = forward - months(1);
	GATS_CHECK(result == back);
	}
#endif
}



GATS_TEST_CASE(ut085_test_Islamic_add_years, ISLAMIC_CALENDAR_GROUP, oneThirteenth) {
#if PHASE_85
	using namespace khronos;
	Islamic date(1433, Muharram, 1);
	Islamic res = date + years(10);
	GATS_CHECK(Islamic(1443, Muharram, 1) == res);
	res = res - years(10);
	GATS_CHECK(res == date);

	// The following won't compile (we made the operator private)
	//res = date + years(10.4);
#endif
}



GATS_TEST_CASE(ut086_test_Islamic_add_years_leapyear, ISLAMIC_CALENDAR_GROUP, oneThirteenth) {
#if PHASE_86
	using namespace khronos;
	Islamic date(1434, DhulHijja, 30, 6, 7, 8);
	Islamic later = date + years(2);
	GATS_CHECK(Islamic(1436, DhulHijja, 30, 6, 7, 8) == later);
	later = date + years(3);
	GATS_CHECK(Islamic(1437, DhulHijja, 29, 6, 7, 8) == later);
#endif
}



GATS_TEST_CASE(ut087_test_Islamic_relational, ISLAMIC_CALENDAR_GROUP, oneThirteenth) {
#if PHASE_87
	using namespace khronos;
	Islamic low(1400, Muharram, 1);
	Islamic high(1400, DhulHijja, 29);
	Islamic copyLow(low);

	GATS_CHECK(low == copyLow);
	GATS_CHECK(low < high);
	GATS_CHECK(low <= copyLow);
	GATS_CHECK(high >= low);
	GATS_CHECK(high > low);
	GATS_CHECK(high != low);
#endif
}



GATS_TEST_CASE(ut088_test_Islamic_to_string, ISLAMIC_CALENDAR_GROUP, oneThirteenth) {
#if PHASE_88
	using namespace khronos;
	GATS_CHECK_EQUAL(Islamic(1000, Muharram, 1).to_string(), std::string("as-sabt, Muharram 1 1000, 12:00:00 am"));
	GATS_CHECK_EQUAL(Islamic(2000, Safar, 29, 12, 0, 0).to_string(), std::string("as-sabt, Safar 29 2000, 12:00:00 pm"));
	GATS_CHECK_EQUAL(Islamic(2010, Rajab, 12, 23, 45, 8).to_string(), std::string("al-jum`a, Rajab 12 2010, 11:45:08 pm"));
	GATS_CHECK_EQUAL(Islamic(-100, Muharram, 1, 6, 7, 8).to_string(), std::string("al-jum`a, Muharram 1 -100, 6:07:08 am"));

	std::ostringstream oss;
	oss << Islamic(2010, Shawwal, 12, 23, 45, 8);
	GATS_CHECK_EQUAL(oss.str(), std::string("al-'arb`a', Shawwal 12 2010, 11:45:08 pm"));
#endif
}
