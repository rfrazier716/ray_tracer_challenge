#include "tracer/geometry/surfaces/uvsurface.hpp"
#include "tracer/geometry/transforms.hpp"

#include "catch.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/epsilon.hpp"

#include <memory> // for smart pointers

using namespace tracer;

SCENARIO("Creating and Probing a Point Surface", "[PointSurface]")
{
	GIVEN("A Point Surface at (1,1,1)")
	{
		auto point = geometry::PointSurface();
		geometry::transform(point, geometry::translationMatrix(1.0f));
		THEN("The origin is at (1,1,1)")
		{
			REQUIRE(vectorEqual(point.getWorldOrigin(), geometry::point(1, 1, 1)));
		}
		THEN("Regardless of u or v, sample should return (1,1,1)")
		{
			auto testPassed = true;
			for (float u = 0; u <= 1.0f; u += 0.1f)
			{
				for (float v = 0; v <= 1.0f; v += 0.1f)
				{
					testPassed &= (vectorEqual(point.sample(u, v), geometry::point(1.0f, 1.0f, 1.0f)));
				}
			}
			REQUIRE(testPassed);
		}
		THEN("A ray from the origin with velocity <1,1,1> should intersect the point at t=1.0f")
		{
			geometry::Intersection hits[2];
			auto ray = geometry::Ray{ geometry::point(0,0,0),geometry::vector(1,1,1) };
			auto nHits = point.findIntersections(ray, hits);
			REQUIRE(nHits == 1);
			REQUIRE(hits[0].t == 1.0f);
		}
		THEN("A ray from the origin with velocity <0,0,1> misses the sphere")
		{
			geometry::Intersection hits[2];
			auto ray = geometry::Ray{ geometry::point(0,0,0),geometry::vector(0,0,1)};
			auto nHits = point.findIntersections(ray, hits);
			REQUIRE(nHits == 0);
		}
	}
}