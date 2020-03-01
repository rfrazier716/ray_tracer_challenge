#pragma once

#define DEFAULT_BRIGHTNESS 200.0f

#include "tracer/colors.hpp"
#include "tracer/geometry/primitives.hpp"
#include "tracer/geometry/surfaces/uvsurface.hpp"

namespace tracer {
	namespace actor
	{
		class Light
		{
		protected:
			COLOR color;
			float brightness;
		public:
			std::unique_ptr<geometry::UVSurface> geometry;
			COLOR getColor() { return color; }
			float getBrightness() { return brightness; }
			/**
			* returns the intensity of the light at the vector objectDirection, which points FROM the lamp TO the object
			*/
			virtual float getIntensity(const VECTOR& objectDirection) { return 0; }
		};

		class PointSource : public Light
		{
		public:
			PointSource(COLOR lightColor = WHITE, float lightBrightness = DEFAULT_BRIGHTNESS);
			float getIntensity(const VECTOR& objectDirection)
			{
				return brightness;
			};
		};
	}
}