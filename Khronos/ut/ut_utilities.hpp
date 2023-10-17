#pragma once

template<typename T>
inline T round(T value, int places) {
	return (T) floor(value * pow(T(10.0), T(places))+0.5) / pow(T(10.0), T(places));
}



/*============================================================================

Revision History

Version 1.0.0: 2015-09-21

==============================================================================
Copyright Garth Santor, 2015

The copyright to the computer program(s) herein
is the property of Garth Santor, Canada.
The program(s) may be used and/or copied only with
the written permission of Garth Santor
or in accordance with the terms and conditions
stipulated in the agreement/contract under which
the program(s) have been supplied.
============================================================================*/