#include "glm/vec4.hpp"	//include a 4d vector for coordinates

inline glm::vec4 point(float x, float y, float z)
{
	return glm::dvec4(x, y, z, 1.0);
}

inline glm::vec4 vector(float x, float y, float z)
{
	return glm::dvec4(x, y, z, 0.0);
}