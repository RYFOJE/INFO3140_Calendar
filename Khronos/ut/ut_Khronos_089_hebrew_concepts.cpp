/*	ut_Khronos_089_hebrew_concepts.cpp

	Khronos library Hebrew Calendar concepts unit test.

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



GATS_TEST_CASE(ut089_test_Hebrew_month_name, HEBREW_CALENDAR_GROUP, 1) {
#if PHASE_89
	using namespace khronos;
	static std::array<std::string, 14> const names = { "",
		"Nisan", "Iyyar", "Sivan", "Tammuz",
		"Av", "Elul", "Tishri", "Heshvan",
		"Kislev", "Teveth", "Shevat", "Adar", "Veadar" };

	for (month_t i = 1; i <= 13; ++i)
		GATS_CHECK(hebrew_month_name(i) == names[i]);
#endif
}
