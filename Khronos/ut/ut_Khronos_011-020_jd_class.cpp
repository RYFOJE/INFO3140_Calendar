/*	ut_Khronos_011-020_jd_class.cpp

	Khronos library Julian Day unit test.

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


GATS_TEST_CASE(ut011_Jdn_differences, GREGORIAN_CALENDAR_GROUP, 1) {
#if PHASE_11
	using namespace khronos;
	Jd past(1000);
	Jd future(2000);

	GATS_CHECK(future - past == 1000);
	GATS_CHECK(past - future == -1000);
#endif
}



/* Default constructor initializes to current time. */
GATS_TEST_CASE(ut012_test_Jd_ctor_default, GREGORIAN_CALENDAR_GROUP, 1) {
#if PHASE_12 
	using namespace khronos;
	time_t utcTime = time(NULL);
	Jd const nowJD;

	struct tm tmLocal;
	localtime_s(&tmLocal, &utcTime);
	jd_t jd = gregorian_to_jd(
		year_t(tmLocal.tm_year) + 1900, month_t(tmLocal.tm_mon + 1), day_t(tmLocal.tm_mday),
		hour_t(tmLocal.tm_hour), minute_t(tmLocal.tm_min), second_t(tmLocal.tm_sec));

	GATS_CHECK_EQUAL(nowJD, jd);
#endif
}



/* Default constructor initializes to current time suppressing time of day. */
GATS_TEST_CASE(ut013_test_Jd_ctor_default_no_time_of_day, GREGORIAN_CALENDAR_GROUP, 2) {
#if PHASE_13
	using namespace khronos;
	time_t utcTime = time(NULL);
	struct tm tmLocal;
	localtime_s(&tmLocal, &utcTime);
	Jd const nowJD(WTIMEOFDAY);
	Jd const nowJDN(NOTIMEOFDAY);

	jd_t jdn = gregorian_to_jd(year_t(tmLocal.tm_year) + 1900, month_t(tmLocal.tm_mon + 1), day_t(tmLocal.tm_mday));
	GATS_CHECK_EQUAL(nowJDN.jd(), jdn);

	jd_t jd = gregorian_to_jd(
		year_t(tmLocal.tm_year) + 1900, month_t(tmLocal.tm_mon + 1), day_t(tmLocal.tm_mday),
		hour_t(tmLocal.tm_hour), minute_t(tmLocal.tm_min), second_t(tmLocal.tm_sec));
#endif
}



/** Test literal constructors. */
GATS_TEST_CASE(ut014_test_Jd_ctor_literal, GREGORIAN_CALENDAR_GROUP, 1) {
#if PHASE_14
	using namespace khronos;
	Jd const epochJdn(-0.5);
	GATS_CHECK(-0.5 == epochJdn);
#endif
}



GATS_TEST_CASE(ut015_test_Jd_add_days, GREGORIAN_CALENDAR_GROUP, 1) {
#if PHASE_15
	using namespace khronos;
	Jd d(2000);
	Jd res = d + days(10);
	GATS_CHECK(res.jd() == 2010);
	res = res - days(10);
	GATS_CHECK(res.jd() == 2000);
#endif
}



GATS_TEST_CASE(ut016_test_Jd_add_weeks, GREGORIAN_CALENDAR_GROUP, 1) {
#if PHASE_16
	using namespace khronos;
 	Jd d(2000);
	Jd res = d + weeks(10);
	GATS_CHECK(d + days(70) == res);
	res = res - weeks(10);
	GATS_CHECK(d == res);
#endif
}



GATS_TEST_CASE(ut017_test_Jd_add_years, GREGORIAN_CALENDAR_GROUP, 1) {
#if PHASE_17
	using namespace khronos;
	Jd d = 2000;
	double const astroYears = 10.4;
	Jd res = d + years(astroYears);
	GATS_CHECK(2000 + EARTH_ORBITAL_PERIOD_DAYS * astroYears == res);
	res = d - years(astroYears);
	GATS_CHECK(2000 - EARTH_ORBITAL_PERIOD_DAYS * astroYears == res);
#endif
}



GATS_TEST_CASE(ut018_test_Jd_day_of_week, GREGORIAN_CALENDAR_GROUP, 1) {
#if PHASE_18
	using namespace khronos;
	Gregorian g(2012, September, 24);  // a monday

	GATS_CHECK(day_of_week(g) == Monday);
#endif
}



GATS_TEST_CASE(ut019_Test_Jd_relational, GREGORIAN_CALENDAR_GROUP, 1) {
#if PHASE_19
	using namespace khronos;
	Jd low(2009);
	Jd high(2010);
	Jd copyLow(low);

	GATS_CHECK(low == copyLow);
	GATS_CHECK(low < high);
	GATS_CHECK(low <= copyLow);
	GATS_CHECK(high >= low);
	GATS_CHECK(high > low);
	GATS_CHECK(high != low);
#endif
}



GATS_TEST_CASE(ut020_test_Jd_to_string, GREGORIAN_CALENDAR_GROUP, 1) {
#if PHASE_20
	using namespace khronos;
	GATS_CHECK_EQUAL(Jd(0).to_string(), std::string("JD 0"));
	GATS_CHECK_EQUAL(Jd(10'000).to_string(), std::string("JD 10000"));
	GATS_CHECK_EQUAL(Jd(-10).to_string(), std::string("JD -10"));

	std::ostringstream oss;
	oss << Jd(0.5);
	GATS_CHECK_EQUAL(oss.str(), std::string("JD 0.5"));
#endif
}
