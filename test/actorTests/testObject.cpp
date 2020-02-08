#include "tracer/actors/object.hpp"
#include "tracer/geometry/primitives.hpp"

#include "catch.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/epsilon.hpp"

using namespace tracer;
SCENARIO("Creating and probing an object", "[Object]")
{
	GIVEN("A new Object instance")
	{
		auto obj = actor::Object();
		THEN("The world coordinate should be a point(0,0,0)")
		{
			REQUIRE(glm::all(glm::equal(obj.getWorldCoordinate(), geometry::point(0, 0, 0))));
		}
	}
}