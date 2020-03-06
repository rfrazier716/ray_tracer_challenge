#pragma once

#include "tracer/canvas.hpp"
#include "tracer/geometry/geometry.hpp"

namespace tracer {
	namespace actor
	{
		class Camera {
		private:

		public:
			geometry::pUVSurface geometry;
			virtual geometry::Ray getCartesianRay(float x, float y){return geometry::Ray{};}
			virtual geometry::Ray getPixelRay(int xPx, int yPx){return geometry::Ray{};}
			virtual geometry::Ray getRandomRay(){return geometry::Ray{};}
		};
	}
}