#pragma once

#include "glm/vec4.hpp"

#define POINT glm::vec4
#define VECTOR glm::vec4

#define X_AXIS vector(1,0,0)
#define Y_AXIS vector(0,1,0)
#define Z_AXIS vector(0,0,1)

namespace tracer 
{
	namespace geometry 
	{
		inline glm::vec4 point(float x, float y, float z) { return glm::vec4(x, y, z, 1); }
		inline glm::vec4 vector(float x, float y, float z) { return glm::vec4(x, y, z, 0); }

		inline void toPoint(glm::vec4& vect) { vect.w = 1;} // pass a vector by reference and set its weight to 1
		inline void toVector(glm::vec4& p) { p.w = 0; } // pass a point by reference and set the weight to 0
	}
}


