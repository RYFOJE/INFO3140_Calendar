#pragma once

/*
khronos\def.hpp
(c) Garth Santor
Created: 2015-09-22
Last Updated: 2015-09-22

Khronos library definitions.
*/

namespace khronos {
	// Note: fundamental data types are signed to simplifies subtractions. * /
	using second_t = double;
	using minute_t = int;
	using hour_t = int;

	using tod_t = double;

	using day_t = int;
	using month_t = int;
	using year_t = long long;

	/** Indicates the 'now' type used by default constructors. */
	enum now_t { NOTIMEOFDAY = 0, WTIMEOFDAY };

	// VALUES
	constexpr double EARTH_ORBITAL_PERIOD_DAYS = 365.256'363'004;
	constexpr second_t SECONDS_PER_DAY = 86'400;

	// Define user-defined literals for _pm and _am
	constexpr int operator "" _pm(unsigned long long hours) {
		return (static_cast<int>(hours) % 12 + 12);
	}

	constexpr int operator "" _am(unsigned long long hours) {
		return static_cast<int>(hours) % 12;
	}

} // end-of-namespace khronos
