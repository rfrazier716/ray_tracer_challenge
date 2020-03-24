#pragma once

#define DEFAULT_BRIGHTNESS 200.0f

#include "tracer/core/actors/actor.hpp"
#include "tracer/core/lightray.hpp"
#include "tracer/colors.hpp"

namespace tracer {
	namespace actor
	{
		/**
		* Parent class for all lights
		*
		*/
		class Light : public Actor
		{
		protected:
			COLOR color;
			float brightness;
		public:
			COLOR getColor() { return color; }
			float getBrightness() { return brightness; }
			/**
			* returns the intensity of the light at the vector objectDirection, which points FROM the lamp TO the object
			*/
			virtual float getIntensity(const VECTOR& objectDirection) { return 0; }
		};
		typedef std::unique_ptr<Light> pLight;
		typedef std::shared_ptr<Light> pSLight;

		/**
		* A point light source that radiates with equal intensity in every direction 
		*
		*/
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