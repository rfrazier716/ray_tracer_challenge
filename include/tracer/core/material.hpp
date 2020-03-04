#pragma once
#include "tracer/colors.hpp"

namespace tracer
{
	struct PhongMaterial
	{
		COLOR color = WHITE;
		float ambient = 0.1f;
		float diffuse = 1.0f;
		float specular = 1.0f;
		float shininess = 200.0f;
	};
}