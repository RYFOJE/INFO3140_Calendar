/*	ut_Khronos_043-045_julian_conv.cpp

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
#include <iomanip>
#include <sstream>
using namespace std;



/** Test known Julian to JD conversions. */
GATS_TEST_CASE(ut043_test_Julian_to_jd, JULIAN_CALENDAR_GROUP, 2) {
#if PHASE_43
	using namespace khronos;

	auto test = [this](year_t year, month_t month, day_t day, jd_t jdn, int line) {
		auto jg = julian_to_jd(year, month, day);
		ostringstream oss;
		oss << fixed << setprecision(10) << "jg(" << jg << ") != jdn(" << jdn << ") from line: " << line;
		GATS_CHECK_MESSAGE(jg == jdn, oss.str());
	};

	test(-4712, January, 1, -0.5, __LINE__);				// beginning of the Julian Epoch
	test(1, January, 1, JULIAN_EPOCH, __LINE__);			// January 1, 1 CE
	test(1582, October, 5, 2'299'160.5, __LINE__);			// Gregorian adoption date Spain, Portugal, Polish-Lithuanian Commonwealth, Papal
	test(1582, December, 10, 2'299'226.5, __LINE__);		// Gregorian adoption date France
	test(1752, September, 3, 2'361'221.5, __LINE__);		// Gregorian adoption date British Empire
	test(1858, November, 4, 2'400'000 - 0.5, __LINE__);
	test(2012, September, 1, 2'456'184.5, __LINE__);
	test(2132, August, 17, 2'500'000 - 0.5, __LINE__);


	auto test2 = [this](year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t seconds, jd_t jdn, int line) {
		auto jg = julian_to_jd(year, month, day, hour, minute, seconds);
		ostringstream oss;
		oss << fixed << setprecision(10) << "jg(" << jg << ") != jdn(" << jdn << ") from line: " << line;
		GATS_CHECK_MESSAGE(jg == jdn, oss.str());
	};
	test2(2132, August, 17, 12, 0, 0, 2'500'000, __LINE__);
	test2(2132, August, 17, 6, 0, 0, 2'500'000 - 0.25, __LINE__);
	test2(2132, August, 17, 18, 0, 0, 2'500'000 + 0.25, __LINE__);
	test2(2132, August, 17, 12, 0, 1, 2'500'000 + 1.0 / (24 * 60 * 60), __LINE__);
#endif
}



/**	Test known JD to Julian conversions. */
GATS_TEST_CASE(ut044_jdn_to_julian_test, JULIAN_CALENDAR_GROUP, 2) {
#if PHASE_44
	using namespace khronos;

	auto test = [this](year_t year, month_t month, day_t day, jd_t jdn, int line) {
		year_t y;
		month_t m;
		day_t d;
		jd_to_julian(jdn, y, m, d);

		ostringstream ossY;
		ossY << "y(" << y << ") != year(" << year << " from line: " << line;
		GATS_CHECK_MESSAGE(y == year, ossY.str());

		ostringstream ossM;
		ossM << "m(" << m << ") != month(" << month << " from line: " << line;
		GATS_CHECK_MESSAGE(m == month, ossM.str());

		ostringstream ossD;
		ossD << "d(" << d << ") != day(" << day << " from line: " << line;
		GATS_CHECK_MESSAGE(d == day, ossD.str());
	};

	test(4713_BC, January, 1, -0.5, __LINE__);			// beginning of the Julian Epoch
	test(1, January, 1, JULIAN_EPOCH, __LINE__);		// January 1, 1 CE
	test(1582, October, 5, 2'299'160.5, __LINE__);		// Gregorian adoption date Spain, Portugal, Polish-Lithuanian Commonwealth, Papal
	test(1582, December, 10, 2'299'226.5, __LINE__);		// Gregorian adoption date France
	test(1752, September, 3, 2'361'221.5, __LINE__);		// Gregorian adoption date British Empire
	test(1858, November, 4, 2'400'000 - 0.5, __LINE__);
	test(2012, September, 1, 2'456'184.5, __LINE__);
	test(2132, August, 17, 2'500'000 - 0.5, __LINE__);


	auto test2 = [this](year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second, jd_t jdn, int line) {
		year_t y;
		month_t m;
		day_t d;
		hour_t h;
		minute_t mi;
		second_t s;
		jd_to_julian(jdn, y, m, d, h, mi, s);

		ostringstream ossY;
		ossY << "y(" << y << ") != year(" << year << " from line: " << line;
		GATS_CHECK_MESSAGE(y == year, ossY.str());

		ostringstream ossM;
		ossM << "m(" << m << ") != month(" << month << " from line: " << line;
		GATS_CHECK_MESSAGE(m == month, ossM.str());

		ostringstream ossD;
		ossD << "d(" << d << ") != day(" << day << " from line: " << line;
		GATS_CHECK_MESSAGE(d == day, ossD.str());

		ostringstream ossH;
		ossY << "h(" << h << ") != hour(" << hour << " from line: " << line;
		GATS_CHECK_MESSAGE(h == hour, ossH.str());

		ostringstream ossMi;
		ossMi << "mi(" << mi << ") != minute(" << minute << " from line: " << line;
		GATS_CHECK_MESSAGE(mi == minute, ossMi.str());

		ostringstream ossS;
		ossS << "s(" << s << ") != second(" << second << " from line: " << line;
		GATS_CHECK_MESSAGE(s == second, ossS.str());
	};
	test2(2132, August, 17, 12, 0, 0, 2'500'000, __LINE__);
	test2(2132, August, 17, 6, 0, 0, 2'500'000 - 0.25, __LINE__);
	test2(2132, August, 17, 18, 0, 0, 2'500'000 + 0.25, __LINE__);
	test2(2132, August, 17, 12, 0, 1, 2'500'000 + 1.0 / (24 * 60 * 60), __LINE__);
#endif
}



/**	Check all conversions from the lowest Proleptic Julian date, until a day well in the future. */
GATS_TEST_CASE(ut045_test_julian_full, JULIAN_CALENDAR_GROUP, 1) {
#if PHASE_45
	using namespace khronos;

	cout << "Starting Julian FULL_TEST: ";
	jd_t low = julian_to_jd(-4799, January, 1);
	jd_t high = julian_to_jd(4800, January, 1);
	for (jd_t jd = low; jd <= high; jd += 0.125) {
		year_t year;
		month_t month;
		day_t day;
		jd_to_julian(jd, year, month, day);
		jd_t result = julian_to_jd(year, month, day);
		GATS_CHECK_EQUAL(jd_to_jdn(jd)-0.5, result);
		hour_t hours;
		minute_t minutes;
		second_t seconds;
		jd_to_julian(jd, year, month, day, hours, minutes, seconds);
		result = julian_to_jd(year, month, day, hours, minutes, seconds);
		GATS_CHECK_EQUAL(jd, result);
	}
	cout << "... completed\n";
#endif
}
