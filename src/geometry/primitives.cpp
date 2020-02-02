#include "tracer/geometry/primitives.hpp"

glm::vec4 point(float x, float y, float z)
{
	return glm::vec4(x, y, z, 1.0);
}

glm::vec4 vector(float x, float y, float z)
{
	return glm::vec4(x, y, z, 0.0);
}