#pragma once

#define _USE_MATH_DEFINES // for C++
#include <math.h>

namespace tracer
{
	inline float toRad(float degree) { return (degree * M_PI / 180.0); }
	//converts degree to radians

	inline float toDeg(float rad) { return (rad * 180.0 / M_PI); }
	//converts radians to degrees
}