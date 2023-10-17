#pragma once

#include <cmath>


namespace khronos {

	namespace utility {
		inline double mod(double a, double b) { return a - b * floor(a / b); }
		inline double jwday(double j) { return mod(floor(j + 1.5), 7.0); }
	}

} // end-of-namespace khronos