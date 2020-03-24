#pragma once

#include "tracer/geometry/geometry.hpp"
#include "tracer/colors.hpp"

namespace tracer 
{
	struct LightRay
	{
		COLOR color = WHITE; //!<  Color of the light, as RGB
		float intensity = 100.0f; //!<  Intensity of the light, arbitrary units

		int generationNumber = 1; //!<  How many times the ray has been generated, gets increments after every ray intersection
		float opticalPathLength = 0.0f; //!<  path length of the light ray, is 

		geometry::Ray geometry; //!<  The geometric parameters of the ray, this is a ray struct with position and direction
	};
}

