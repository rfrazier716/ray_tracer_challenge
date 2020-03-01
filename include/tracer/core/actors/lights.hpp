#pragma once

#include "tracer/colors.hpp"
#include "tracer/geometry/primitives.hpp"

namespace tracer {
	class Light 
	{
	protected:
		COLOR color;
		POINT position;
		VECTOR direction;
		float brightness;
	public:
		/**
		* returns the intensity of the light at the vector objectDirection, which points FROM the lamp TO the object
		*/
		virtual float getIntensity(const VECTOR& objectDirection) { return 0; }
	};

	class PointSource : public Light
	{
		float getIntensity(const VECTOR& objectDirection) 
		{
			return brightness;
		};
	};
}