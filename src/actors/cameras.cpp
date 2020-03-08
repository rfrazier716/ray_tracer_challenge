#include "tracer/core/actors/cameras.hpp"

using namespace tracer;

geometry::Ray tracer::actor::OrthoCamera::getRay(int xPx, int yPx, int renderWidth, int renderHeight)
{
	float rayOffsetX = width * (xPx / renderWidth - 0.5f);
	float rayOffsetY = width * renderHeight/renderWidth * (yPx / renderHeight- 0.5f);
	auto ray = geometry::Ray{ geometry::point(rayOffsetX,rayOffsetY,0),geometry::vector(0,0,1.0f) };
	geometry::transform(ray, surfaceGeometry->getWorldTransform());
	return ray;
}

