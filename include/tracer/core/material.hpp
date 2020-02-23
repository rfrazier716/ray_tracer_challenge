#include "tracer/colors.hpp"

namespace tracer
{
	struct PhongMaterial
	{
		COLOR color = WHITE;
		auto ambient = 0.1f;
		auto diffuse = 1.0f;
		auto specular = 1.0f;
		auto shininess = 200.0f;
	};
}