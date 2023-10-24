#pragma once

/*
khronos\timeofday.hpp
(c) Garth Santor
Created: 2015-09-22
Last Updated: 2015-09-22

Khronos library 'time-of-day' declarations.
*/


#include <khronos/def.hpp>
#include <khronos/utility.hpp>


namespace khronos {
	// LITERALS


	/* UDL - converts an 'AM' hour to 'military' hour. */
	constexpr int operator "" _am(unsigned long long hours) {
		return static_cast<int>(hours) % 12;
	}


	/* UDL - converts an 'PM' hour to 'military' hour. */
	constexpr int operator "" _pm(unsigned long long hours) {
		return (static_cast<int>(hours) % 12 + 12);
	}


	/* Seconds per day. */
	constexpr second_t SECONDS_PER_DAY = 86'400;


	/* H:M:S.S to time-of-day [0.0..1.0) */
	constexpr tod_t tod(hour_t hours, minute_t minutes, second_t seconds) {
		return (seconds + 60 * (minutes + 60 * hours)) / SECONDS_PER_DAY;
	}

	constexpr tod_t tod_middle(hour_t hours, minute_t minutes, second_t seconds) {
		return -1 + tod(hours, minutes, seconds);
	}

	/**	Convert Time-of-day (TOD) to hours, minutes, seconds.  Civil days run from midnight to midnight.
		@param tod [in] a time-of-day [0..1)
		@param hours [out] 0-23
		@param minutes [out] 0-59
		@param seconds [out] [0.0..60.0)
	*/
	constexpr tod_t time_of_day(hour_t hours, minute_t minutes, second_t seconds) {

		return (seconds + 60.0 * (minutes + 60.0 * hours))
			/ (24.0 * 60.0 * 60.0);

	}

	inline void tod_to_hms(const tod_t tod, hour_t& hours, minute_t& minutes, second_t& seconds) {
		
		// TODO Check to see if I can use int instead as this value will always be floored
		long long secondsInDay = static_cast<long long>(floor(tod * 24 * 60 * 60 + 0.5));

		// TODO Test to see if this is a valid way of doing it with modulo
		hours = static_cast<hour_t>(secondsInDay / (60.0 * 60.0)) + 12;
		hours %= 24;

		// TODO Find better implementation of namespace
		minutes = static_cast<minute_t>(utility::mod(static_cast<double>(secondsInDay / 60.0), 60));
		seconds = static_cast<minute_t>(utility::mod(static_cast<double>(secondsInDay), 60));
	}
	

} // end-of-namespace khronos
