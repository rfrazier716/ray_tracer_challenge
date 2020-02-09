#include "tracer/geometry/primitives.hpp"
#include "tracer/math.hpp"

#include "catch.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/epsilon.hpp"


using namespace tracer;

SCENARIO("Defining a new Ray structure ", "[rayTest]")
{
	GIVEN("A Ray object at the origin pointing to <0,0,1>")
	{
		auto ray = geometry::Ray{ geometry::point(0,0,0), geometry::vector(0,0,1) };
		THEN("ray.position = (0,0,0) and ray.direction = (0,0,1)")
		{
			REQUIRE(vectorEqual(ray.position,geometry::point(0, 0, 0)));
			REQUIRE(vectorEqual(ray.direction, geometry::vector(0, 0, 1)));
			AND_THEN("Sampling the ray at any time t results in the point (0,0,t)")
			{
				auto raySamplingFunctional = true;
				for (float t = -10.0; t < 10.0; t += 0.01f)
				{
					if (!vectorEqual(geometry::sampleRay(ray,t),geometry::point(0,0,t)))
					{
						raySamplingFunctional = false;
					}
				}
				REQUIRE(raySamplingFunctional);
			}
		}

	}
}