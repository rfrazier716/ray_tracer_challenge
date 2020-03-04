#include "tracer/core/actors/lights.hpp"

using namespace tracer;

//Helper Functions for lights
void geometry::transform(actor::Light& light, glm::mat4 const& transformMatrix)
{
	geometry::transform(*(light.geometry), transformMatrix);
}

//Class function for pointsource
actor::PointSource::PointSource(COLOR lightColor, float lightBrightness)
{
	color = lightColor;
	brightness = lightBrightness;
	geometry = std::make_unique<geometry::PointSurface>();
}