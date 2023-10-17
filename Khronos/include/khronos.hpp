#pragma once

/*
khronos.hpp
(c) Garth Santor
Created: 2015-09-19
Last Updated: 2015-09-20

Khronos library header.
*/


#include <khronos/def.hpp>
#include <khronos/julian_day.hpp>
#include <khronos/timeofday.hpp>
#include <khronos/gregorian_calendar.hpp>
#include <khronos/julian_calendar.hpp>
#include <khronos/islamic_calendar.hpp>
#include <khronos/hebrew_calendar.hpp>
#include <khronos/vulcan_calendar.hpp>

// Define user-defined literals for _pm and _am
constexpr int operator "" _pm(unsigned long long hours) {
    return (static_cast<int>(hours) % 12 + 12);
}

constexpr int operator "" _am(unsigned long long hours) {
    return static_cast<int>(hours) % 12;
}