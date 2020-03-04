#pragma once

#define _USE_MATH_DEFINES // for C++
#define F_PI (float) M_PI
#include <math.h>
#include "glm/gtc/epsilon.hpp"

namespace tracer
{
	inline float toRad(float degree) { return (degree * F_PI / 180.0f); }
	//converts degree to radians

	inline float toDeg(float rad) { return (rad * 180.0f / F_PI); }
	//converts radians to degrees
	
	template<class T>
	inline bool vectorEqual(T vecA, T vecB, float epsilon = 1e-6f) 
	{ 
		return glm::all(glm::epsilonEqual(
			vecA, 
			vecB, 
			T(epsilon)
		)); 
	}

	template<class T>
	static bool areSame(T a, T b, T epsilon) { return std::fabs(a - b) < epsilon; }
}