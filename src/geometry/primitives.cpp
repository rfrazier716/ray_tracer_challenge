#include "tracer/geometry/primitives.hpp"


using namespace tracer; //tracer namespace for the project

glm::vec4 geometry::point(float x, float y, float z)
{
	return glm::vec4(x, y, z, 1.0);
}

glm::vec4 geometry::vector(float x, float y, float z)
{
	return glm::vec4(x, y, z, 0.0);
}