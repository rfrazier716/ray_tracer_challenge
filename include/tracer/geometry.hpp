#include "glm/vec4.hpp"	//include a 4d vector for coordinates

#define _USE_MATH_DEFINES // for C++
#include <math.h>

inline glm::vec4 point(float x, float y, float z)
{
	return glm::vec4(x, y, z, 1.0);
}

inline glm::vec4 vector(float x, float y, float z)
{
	return glm::vec4(x, y, z, 0.0);
}


float rad(float degree);
//converts degree to radians

float deg(float rad);
//converts radians to degrees
