#pragma once
/*	julian_day.hpp

	Khronos library Julian Day class declaration.

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.09.25
	Replaced relational operators with <=>

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

#include <cmath>
#include <string>
#include <ostream>

#include <khronos/def.hpp>
#include <khronos/timeofday.hpp>
#include <khronos/utility.hpp>
#include <khronos/calendar.hpp>



namespace khronos {

	// Type definitions
	using jd_t = double;

	// VALUES
	constexpr jd_t GREGORIAN_EPOCH = 173'651.6;

	
	// FUNCTIONS

	jd_t jd_to_jdn(jd_t jd);

	void jd_to_gregorian(jd_t jd, year_t& year, month_t& month, day_t& day);

	void jd_to_gregorian(jd_t jd, year_t& year, month_t& month, day_t& day,
		hour_t& hours, minute_t& minutes, second_t& seconds);

	civil_weekday_codes_long day_of_week(const jd_t jd);
	

	/** JD CLASS DEFINITION **/

	class Jd {

		jd_t jd_;

	public:
		Jd();
		Jd(now_t now);
		constexpr Jd(double time) : jd_(time) {};
		
		constexpr jd_t jd() const { return jd_; }
		std::string to_string() const;
	};


	// FUNCTIONS ON JD CLASS

	/** stream insertion operator. */
	inline std::ostream& operator << (std::ostream& os, Jd const& jd) {
		return os << jd.to_string();
	}

	/** Jd relational operators. */
	constexpr auto operator <=> (Jd const& lhs, Jd const& rhs) { return lhs.jd() <=> rhs.jd(); }
	constexpr auto operator == (Jd const& lhs, Jd const& rhs) { return lhs.jd() == rhs.jd(); }

	/**Jd difference operator. */
	constexpr jd_t operator - (Jd const& lhs, Jd const& rhs) { return lhs.jd() - rhs.jd(); }


	// JD DAYS
	/** Jd add days operator */
	constexpr Jd operator + (Jd const& lhs, days const& rhs) { 
		return Jd(lhs.jd() + rhs.count);
	}

	/*Jd remove days operator */
	constexpr Jd operator - (Jd const& lhs, days const& rhs) {
		return Jd(lhs.jd() - rhs.count);
	}

	// JD WEEKS
	/*Jd add weeks operator */
	constexpr Jd operator + (Jd const& lhs, weeks const& rhs) {
		return Jd(lhs.jd() + rhs.count * DAYS_IN_WEEK);
	}

	/*Jd subtract weeks operator */
	constexpr Jd operator - (Jd const& lhs, weeks const& rhs) {
		return Jd(lhs.jd() - rhs.count * DAYS_IN_WEEK);
	}

	// JD YEARS
	/*Jd add years operator */
	constexpr Jd operator + (Jd const& lhs, years const& rhs) {
		return Jd(lhs.jd() + rhs.count * EARTH_ORBITAL_PERIOD_DAYS);
	}

	/*Jd subtract years operator */
	constexpr Jd operator - (Jd const& lhs, years const& rhs) {
		return Jd(lhs.jd() - rhs.count * EARTH_ORBITAL_PERIOD_DAYS);
	}




} // end-of-namespace khronos