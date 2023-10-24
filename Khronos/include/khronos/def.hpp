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
	using jd_t = double;

	using day_t = int;
	using month_t = int;
	using year_t = long long;

	/** Indicates the 'now' type used by default constructors. */
	enum now_t { NOTIMEOFDAY = 0, WTIMEOFDAY };

	// VALUES
	constexpr double EARTH_ORBITAL_PERIOD_DAYS = 365.256'363'004;
	constexpr jd_t GREGORIAN_EPOCH = 173'651.6;
	constexpr jd_t ISLAMIC_EPOCH = 1'948'439.5;
	constexpr jd_t HEBREW_EPOCH = 347'995.5;
	constexpr int DAYS_IN_WEEK = 7;


} // end-of-namespace khronos
