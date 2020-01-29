#include "tracer/geometry.hpp"

glm::vec4 point(float x, float y, float z)
{
	return glm::vec4(x, y, z, 1.0);
}

glm::vec4 vector(float x, float y, float z)
{
	return glm::vec4(x, y, z, 0.0);
}

float toRad(float degree) { return (degree * M_PI / 180.0); }
//converts degree to radians

float toDeg(float rad) { return (rad * 180.0 / M_PI); }
//converts radians to degrees
