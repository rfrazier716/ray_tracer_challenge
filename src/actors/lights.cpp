#include "tracer/core/actors/lights.hpp"

using namespace tracer;

//Class function for pointsource
actor::PointSource::PointSource(COLOR lightColor, float lightBrightness)
{
	color = lightColor;
	brightness = lightBrightness;
	surfaceGeometry = std::make_unique<geometry::PointSurface>();
}