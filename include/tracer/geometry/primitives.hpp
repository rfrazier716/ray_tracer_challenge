#pragma once

#include "glm/vec4.hpp"

#define POINT glm::vec4
#define VECTOR glm::vec4

#define X_AXIS geometry::vector(1,0,0)
#define Y_AXIS geometry::vector(0,1,0)
#define Z_AXIS geometry::vector(0,0,1)

namespace tracer 
{
	namespace geometry 
	{
		struct Ray
		{
			POINT position;
			POINT direction;
		};
		static POINT sampleRay(Ray ray, float t) { return ray.position + t * ray.direction; }

		/**
		* 
		* /brief an intersection records the intersection between a ray and a surface
		*
		* holds the t value of the ray as well as the u,v parameters of surface where the intersection occurs
		* 
		*/

		struct Intersection
		{
			float t;
			float u;
			float v;
		};

		inline glm::vec4 point(float x, float y, float z) { return glm::vec4(x, y, z, 1); }
		inline glm::vec4 vector(float x, float y, float z) { return glm::vec4(x, y, z, 0); }

		inline glm::vec4 toPoint(glm::vec4& v) { return glm::vec4(v.x, v.y, v.z, 1.0f);} // pass a vector by reference and set its weight to 1
		inline glm::vec4 toVector(glm::vec4& p) { return glm::vec4(p.x,p.y,p.z,0); } // pass a point by reference and set the weight to 0


	}
}


