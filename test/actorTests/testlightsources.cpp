#include "tracer/tracer.hpp"

#include "catch.hpp"

using namespace tracer;

template<class T>
void logVector(T vect)
{
	for (int j = 0; j < vect.length(); j++)
	{
		std::cout << vect[j] << " ";
	}
	std::cout << std::endl;
}

SCENARIO("Creating and Probing a Point Source", "[Lights]")
{
	GIVEN("A Default Light Source")
	{
		auto light = actor::PointSource();
		THEN("The color is white and it's brightness is default")
		{
			REQUIRE(vectorEqual(light.getColor(), WHITE));
			REQUIRE(light.getBrightness() == DEFAULT_BRIGHTNESS);
			AND_THEN("The Intensity is equal in every direction")
			{
				auto sphere = geometry::SphericalSurface();
				auto testPassed = true;
				for (float u = 0; u <= 1.0f; u += 0.1f)
				{
					for (float v = 0; v <= 1.0f; v += 0.1f)
					{
						testPassed &= (light.getIntensity(sphere.sample(u,v))== DEFAULT_BRIGHTNESS);
					}
				}
				REQUIRE(testPassed);
			}
			AND_THEN("Moving the light moves the origin and direction")
			{
				//rotate by 180 degrees and then move to 3,3,3
				auto tMat = geometry::translationMatrix(3.0f) * geometry::rotationMatrix(F_PI, X_AXIS) * geometry::scaleMatrix(10.0f);
				geometry::transform(*(light.surfaceGeometry), tMat);
				logVector(light.surfaceGeometry->getWorldOrientation());
				REQUIRE(vectorEqual(light.surfaceGeometry->getWorldOrientation(), geometry::vector(0, 0, -1.0f)));
				logVector(light.surfaceGeometry->getWorldOrigin());
				REQUIRE(vectorEqual(light.surfaceGeometry->getWorldOrigin(), geometry::point(3.0f,3.0f,3.0f)));
			}
		}
	}
}