/*	ut_khronos_046-063_julian_class.cpp

	Khronos library Julian Calendar class unit test.

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

constexpr double oneThird = 1.0 / 3.0;



/* Default constructor initializes to current time. */
GATS_TEST_CASE(ut046_test_Julian_ctor_default, JULIAN_CALENDAR_GROUP, oneThird) {
#if PHASE_46
	using namespace khronos;
	time_t utcTime = time(NULL);
	Julian const	now;
	Julian const today(NOTIMEOFDAY);
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



GATS_TEST_CASE(ut047_test_Julian_ctor_literal, JULIAN_CALENDAR_GROUP, oneThird) {
#if PHASE_47
	using namespace khronos;
	Julian const epochJulian(4713_BC, January, 1);
	GATS_CHECK(4713_BC == epochJulian.year());
	GATS_CHECK(January == epochJulian.month());
	GATS_CHECK(1 == epochJulian.day());

	Julian const greatWar(1918, October, 29, 11, 11, 11);
	GATS_CHECK(1918 == greatWar.year());
	GATS_CHECK(October == greatWar.month());
	GATS_CHECK(29 == greatWar.day());
	GATS_CHECK(11 == greatWar.hour());
	GATS_CHECK(11 == greatWar.minute());
	GATS_CHECK(11 == greatWar.second());
#endif
}



GATS_TEST_CASE(ut048_test_Julian_ctor_from_Jd, JULIAN_CALENDAR_GROUP, oneThird) {
#if PHASE_48
	using namespace khronos;
	Julian g(Jd(-0.5));
	GATS_CHECK_EQUAL(g.year(), 4713_BC);
	GATS_CHECK_EQUAL(g.month(), January);
	GATS_CHECK_EQUAL(g.day(), 1);
	GATS_CHECK_EQUAL(g.hour(), 0);
	GATS_CHECK_EQUAL(g.minute(), 0);
	GATS_CHECK_EQUAL(g.second(), 0);
#endif
}



GATS_TEST_CASE(ut049_test_Julian_cast_to_Jd, JULIAN_CALENDAR_GROUP, oneThird) {
#if PHASE_49
	using namespace khronos;
	Julian const	julianEpoch(4713_BC, January, 1);
	Jd je = julianEpoch;
	GATS_CHECK_EQUAL(je.jd(), -0.5);
#endif
}



GATS_TEST_CASE(ut050_test_Julian_assignment_from_Jd, JULIAN_CALENDAR_GROUP, oneThird) {
#if PHASE_50
	using namespace khronos;
	Julian g;
	g = Jd(-0.5);
	GATS_CHECK_EQUAL(g.year(), 4713_BC);
	GATS_CHECK_EQUAL(g.month(), January);
	GATS_CHECK_EQUAL(g.day(), 1);
	GATS_CHECK_EQUAL(g.hour(), 0);
	GATS_CHECK_EQUAL(g.minute(), 0);
	GATS_CHECK_EQUAL(g.second(), 0);
#endif
}



GATS_TEST_CASE(ut051_test_Julian_add_days, JULIAN_CALENDAR_GROUP, oneThird) {
#if PHASE_51
	using namespace khronos;
	Julian d(2000, January, 1);
	Julian res = d + days(10);
	GATS_CHECK(res == Julian(2000, January, 11));
	res = res - days(10);
	GATS_CHECK(res == d);
#endif
}



GATS_TEST_CASE(ut052_test_Julian_add_days_with_time, JULIAN_CALENDAR_GROUP, oneThird) {
#if PHASE_52
	using namespace khronos;
	Julian d(2000, January, 1, 12, 13, 14);
	Julian res = d + days(10);
	GATS_CHECK(res == Julian(2000, January, 11, 12, 13, 14));
	res = res - days(10);
	GATS_CHECK(res == d);
#endif
}



GATS_TEST_CASE(ut053_test_Julian_add_weeks, JULIAN_CALENDAR_GROUP, oneThird) {
#if PHASE_53
	using namespace khronos;
	Julian d(2000, JAN, 1);
	Julian res = d + weeks(10);
	GATS_CHECK(d + days(70) == res);
	res = res - weeks(10);
	GATS_CHECK(d == res);
#endif
}



GATS_TEST_CASE(ut054_test_Julian_add_weeks_with_time, JULIAN_CALENDAR_GROUP, oneThird) {
#if PHASE_54
	using namespace khronos;
	Julian d(2000, JAN, 1, 6, 7, 8);
	Julian res = d + weeks(10);
	GATS_CHECK(d + days(70) == res);
	res = res - weeks(10);
	GATS_CHECK(d == res);
#endif
}



GATS_TEST_CASE(ut055_test_Julian_add_months, JULIAN_CALENDAR_GROUP, oneThird) {
#if PHASE_55
	using namespace khronos;
	{	Julian start(2000, JAN, 1);
	Julian end(2000, FEB, 1);
	Julian res = start + months(1);
	GATS_CHECK(end == res);
	res = end - months(1);
	GATS_CHECK(res == start);
	}
	{	Julian start(2000, JAN, 1, 12, 13, 14);
	Julian end(2001, FEB, 1, 12, 13, 14);
	Julian res = start + months(13);
	GATS_CHECK(end == res);
	res = end - months(13);
	GATS_CHECK(res == start);
	}

	// shouldn't compile
	//start + months(1.2);
#endif
}



GATS_TEST_CASE(ut056_test_Julian_add_months_w_carry, JULIAN_CALENDAR_GROUP, oneThird) {
#if PHASE_56
	using namespace khronos;
	{	Julian start(2000, OCT, 1);
	Julian end(2001, FEB, 1);
	Julian res = start + months(4);
	GATS_CHECK(end == res);
	res = end - months(4);
	GATS_CHECK(res == start);
	}
	{	Julian start(2000, OCT, 1, 6, 7, 8);
	Julian end(2003, FEB, 1, 6, 7, 8);
	Julian res = start + months(28);
	GATS_CHECK(end == res);
	res = end - months(28);
	GATS_CHECK(res == start);
	}
#endif
}



GATS_TEST_CASE(ut057_test_Julian_add_month_leap, JULIAN_CALENDAR_GROUP, oneThird) {
#if PHASE_57
	using namespace khronos;
	{	Julian start(2000, February, 29);
	Julian end(2000, March, 29);
	Julian res = start + months(1);
	GATS_CHECK(end == res);
	res = end - months(1);
	GATS_CHECK(res == start);
	}
	{	Julian start(2000, January, 31, 6, 7, 8);
	Julian end(2000, February, 29, 6, 7, 8);
	Julian res = start + months(1);
	GATS_CHECK(end == res);
	res = end - months(1);
	GATS_CHECK(res == Julian(2000, January, 29, 6, 7, 8));
	}
#endif
}



GATS_TEST_CASE(ut058_test_Julian_add_years, JULIAN_CALENDAR_GROUP, oneThird) {
#if PHASE_58
	using namespace khronos;
	Julian date(2000, January, 1);
	Julian result = date + years(10);
	GATS_CHECK(Julian(2010, January, 1) == result);
	result = result - years(10);
	GATS_CHECK(result == date);

	// The following won't compile (we made the operator private)
	//result = date + years(10.4);
#endif
}



GATS_TEST_CASE(ut059_test_Julian_add_years_leapyear, JULIAN_CALENDAR_GROUP, oneThird) {
#if PHASE_59
	using namespace khronos;
	Julian d(2000, February, 29, 12, 13, 14);
	Julian later = d + years(2);
	GATS_CHECK(Julian(2002, February, 28, 12, 13, 14) == later);
#endif
}



GATS_TEST_CASE(ut060_test_Julian_relational, JULIAN_CALENDAR_GROUP, oneThird) {
#if PHASE_60
	using namespace khronos;
	Julian low(2009, 1, 1);
	Julian high(2009, 12, 31);
	Julian copyLow(low);

	GATS_CHECK(low == copyLow);
	GATS_CHECK(low < high);
	GATS_CHECK(low <= copyLow);
	GATS_CHECK(high >= low);
	GATS_CHECK(high > low);
	GATS_CHECK(high != low);
#endif
}



GATS_TEST_CASE(ut061_test_Julian_to_string, JULIAN_CALENDAR_GROUP, oneThird) {
#if PHASE_61
	using namespace khronos;
	GATS_CHECK_EQUAL(Julian(1000, January, 1).to_string(), std::string("Monday, January 1 1000 AD, 12:00:00 am"));
	GATS_CHECK_EQUAL(Julian(2000, February, 29, 12, 30, 11).to_string(), std::string("Monday, February 29 2000 AD, 12:30:11 pm"));
	GATS_CHECK_EQUAL(Julian(2010, September, 12, 23, 45, 8).to_string(), std::string("Saturday, September 12 2010 AD, 11:45:08 pm"));
	GATS_CHECK_EQUAL(Julian(-100, January, 1, 6, 7, 8).to_string(), std::string("Friday, January 1 101 BC, 6:07:08 am"));

	std::ostringstream oss;
	oss << Julian(2010, September, 12, 23, 45, 8);
	GATS_CHECK_EQUAL(oss.str(), std::string("Saturday, September 12 2010 AD, 11:45:08 pm"));
#endif
}



GATS_TEST_CASE(ut062_test_Julian_element_functions, JULIAN_CALENDAR_GROUP, oneThird) {
#if PHASE_62
	using namespace khronos;
	Julian g(2010, September, 12, 23, 45, 8);
	GATS_CHECK_EQUAL(year(g), 2010);
	GATS_CHECK_EQUAL(month(g), September);
	GATS_CHECK_EQUAL(day(g), 12);
	GATS_CHECK_EQUAL(hour(g), 23);
	GATS_CHECK_EQUAL(minute(g), 45);
	GATS_CHECK_EQUAL(second(g), 8);
#endif
}



GATS_TEST_CASE(ut063_julian_differences, JULIAN_CALENDAR_GROUP, oneThird) {
#if PHASE_63
	using namespace khronos;
	Julian past(1858, 11, 16);
	Julian future(2132, 8, 31);

	GATS_CHECK(future - past == 100'002);
	GATS_CHECK(past - future == -100'002);

	Julian start(2000, 1, 1);
	Julian end(2001, 1, 1);

	GATS_CHECK(end - start == 366);
	GATS_CHECK(start - end == -366);
#endif
}
