#include "tracer/core/actors/cameras.hpp"

using namespace tracer;

geometry::Ray tracer::actor::OrthoCamera::getRay(float xPct, float yPct)
{
	auto rayOrigin=surfaceGeometry->getWorldTransform() * geometry::point(0, (xPct - 0.5) * orthoWidth, (0.5-yPct) * orthoWidth*aspectRatio);
	return geometry::Ray{rayOrigin,surfaceGeometry->getWorldTransform() * X_AXIS};
}

