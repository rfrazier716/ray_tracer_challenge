#include "glm/vec4.hpp"	//include a 4d vector for coordinates

#define _USE_MATH_DEFINES // for C++
#include <math.h>

//axes, useful for rotation matrices
#define X_AXIS glm::vec4(1,0,0,0)
#define Y_AXIS glm::vec4(0,1,0,0)
#define Z_AXIS glm::vec4(0,0,1,0)

inline glm::vec4 point(float x, float y, float z)
{
	return glm::vec4(x, y, z, 1.0);
}

inline glm::vec4 vector(float x, float y, float z)
{
	return glm::vec4(x, y, z, 0.0);
}


float toRad(float degree);
//converts degree to radians

float toDeg(float rad);
//converts radians to degrees
