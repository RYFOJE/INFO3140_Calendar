#pragma once

/*
khronos\timeofday.hpp
(c) Garth Santor
Created: 2015-09-22
Last Updated: 2015-09-22

Khronos library 'time-of-day' declarations.
*/


#include <khronos/def.hpp>


namespace khronos {
	// LITERALS
	/* UDL - converts an 'AM' hour to 'military' hour. */




	/* UDL - converts an 'PM' hour to 'military' hour. */


	/* Seconds per day. */



	/* H:M:S.S to time-of-day [0.0..1.0) */


	/**	Convert Time-of-day (TOD) to hours, minutes, seconds.  Civil days run from midnight to midnight.
		@param tod [in] a time-of-day [0..1)
		@param hours [out] 0-23
		@param minutes [out] 0-59
		@param seconds [out] [0.0..60.0)
		*/

} // end-of-namespace khronos
