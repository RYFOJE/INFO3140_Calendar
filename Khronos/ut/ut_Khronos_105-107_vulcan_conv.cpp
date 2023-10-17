/*	ut_Khronos_105-107_vulcan_conv.cpp

	Khronos library Vulcan Calendar conversion unit test.

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
#include <sstream>
#include <iomanip>
using namespace std;

#include "ut_utilities.hpp"



/** Test known Vulcan to JD conversions. */
GATS_TEST_CASE(ut105_test_vulcan_to_jd, VULCAN_CALENDAR_GROUP, 1) {
#if PHASE_105
	using namespace khronos;

	auto test = [this](year_t year, month_t month, day_t day, jd_t jd, int line) {
		auto jg = vulcan_to_jd(year, month, day);
		jg = round(jg, 4);
		jd = round(jd, 4);
		ostringstream oss;
		oss << fixed << setprecision(15) << "jg(" << jg << ") != jd(" << jd << ") from line: " << line;
		GATS_CHECK_MESSAGE(jg == jd, oss.str());
	};

	test(1, Zat, 1, VULCAN_EPOCH, __LINE__);
	test(-651, Druh, 18, -1.028'571'4, __LINE__);					// beginning of the Julian Epoch


	auto test2 = [this](year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t seconds, jd_t jd, int line) {
		auto jg = vulcan_to_jd(year, month, day, hour, minute, seconds);
		jg = round(jg, 4);
		jd = round(jd, 4);
		ostringstream oss;
		oss << fixed << setprecision(10) << "jg(" << jg << ") != jd(" << jd << ") from line: " << line;
		GATS_CHECK_MESSAGE(jg == jd, oss.str());
	};
	test2(1, Zat, 1, 0, 0, 0, VULCAN_EPOCH, __LINE__);
	test2(8733, TaKrat, 10, 15, 4, 20, 2'500'000, __LINE__);
#endif
}



/**	Test known JD to Vulcan conversions. */
GATS_TEST_CASE(ut106_test_jd_to_vulcan, VULCAN_CALENDAR_GROUP, 1) {
#if PHASE_106
	using namespace khronos;

	auto test = [this](year_t year, month_t month, day_t day, jd_t jd, int line) {
		year_t y;
		month_t m;
		day_t d;
		jd_to_vulcan(jd, y, m, d);

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

	test(-651, Druh, 18, 0, __LINE__);						// beginning of the Julian Epoch
	test(1, Zat, 1, VULCAN_EPOCH, __LINE__);


	auto test2 = [this](year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second, jd_t jd, int line) {
		year_t y;
		month_t m;
		day_t d;
		hour_t h;
		minute_t mi;
		second_t s;
		jd_to_vulcan(jd, y, m, d, h, mi, s);

		ostringstream ossY;
		ossY << "y(" << y << ") != year(" << year << ") from line: " << line;
		GATS_CHECK_MESSAGE(y == year, ossY.str());

		ostringstream ossM;
		ossM << "m(" << m << ") != month(" << month << ") from line: " << line;
		GATS_CHECK_MESSAGE(m == month, ossM.str());

		ostringstream ossD;
		ossD << "d(" << d << ") != day(" << day << ") from line: " << line;
		GATS_CHECK_MESSAGE(d == day, ossD.str());

		ostringstream ossH;
		ossH << "h(" << h << ") != hour(" << hour << ") from line: " << line;
		GATS_CHECK_MESSAGE(h == hour, ossH.str());

		ostringstream ossMi;
		ossMi << "mi(" << mi << ") != minute(" << minute << ") from line: " << line;
		GATS_CHECK_MESSAGE(mi == minute, ossMi.str());

		ostringstream ossS;
		ossS << "s(" << s << ") != second(" << second << ") from line: " << line;
		GATS_CHECK_MESSAGE(round(s) == second, ossS.str());
	};
	test2(1, Zat, 1, 0, 0, 0, VULCAN_EPOCH, __LINE__);
	test2(8733, TaKrat, 10, 15, 4, 20, 2'500'000, __LINE__);
#endif
}


/**	Check all conversions from the lowest Proleptic Vulcan date, until a day well in the future. */
GATS_TEST_CASE(ut107_test_vulcan_to_jd_full, VULCAN_CALENDAR_GROUP, 1) {
#if PHASE_107
	using namespace khronos;

	cout << "Starting Vulcan FULL_TEST: ";
	auto increment = 0.1;
	jd_t low = vulcan_to_jd(1, Zat, 1);
	jd_t high = vulcan_to_jd(10'000, Tasmeen, 21);
	for (jd_t jd = low; jd <= high; jd += increment) {
		year_t year;
		month_t month;
		day_t day;
		hour_t hours;
		minute_t minutes;
		second_t seconds;
		jd_to_vulcan(jd, year, month, day, hours, minutes, seconds);
		jd_t result = vulcan_to_jd(year, month, day, hours, minutes, seconds);
		GATS_CHECK_WITHIN(jd, result, 0.000'000'1);
	}
	cout << "... completed\n";
#endif
}
