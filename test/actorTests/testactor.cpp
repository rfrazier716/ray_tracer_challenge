#include "tracer/core/actors/actor.hpp"
#include "testUtils.hpp"
#include "catch.hpp"
#include <memory>

using namespace tracer;

SCENARIO("Creating an Actor")
{
	GIVEN("A new actor object with a point as it's geometry")
	{
		auto a =actor::Actor();
		a.surfaceGeometry = std::make_unique<geometry::PointSurface>();
		THEN("The id of the actor should be 0")
		{
			REQUIRE(a.id == 0);
		}
		THEN("The actor should exist at (0,0,0) facing <1,0,0> with it's normal facing up")
		{
			REQUIRE(vectorEqual(a.surfaceGeometry->getWorldOrigin(), geometry::point(0, 0, 0)));
			REQUIRE(vectorEqual(a.surfaceGeometry->getWorldOrientation(), geometry::vector(0, 0, 1.0f)));
			REQUIRE(vectorEqual(a.surfaceGeometry->getWorldDirection(), geometry::vector(1.0f, 0, 0)));
			AND_THEN("Moving the actor will update the geometry")
			{
				geometry::move(a, -1.0f, 0, 1.0f);
				REQUIRE(vectorEqual(a.surfaceGeometry->getWorldOrigin(), geometry::point(-1.0f, 0, 1.0f)));
				geometry::moveAbs(a, -10.0f, 0, 10.0f);
				REQUIRE(vectorEqual(a.surfaceGeometry->getWorldOrigin(), geometry::point(-10.0f, 0, 10.0f)));				
				AND_THEN("Rotating the actor will update the geometry")
				{
					geometry::moveAbs(a); // reset the position 
					geometry::transform(a, geometry::rotationMatrix(F_PI / 4.0f, Y_AXIS));
					REQUIRE(vectorEqual(a.surfaceGeometry->getWorldDirection(), glm::normalize(geometry::vector(1.0f, 0, -1.0f))));
					REQUIRE(vectorEqual(a.surfaceGeometry->getWorldOrientation(), glm::normalize(geometry::vector(1.0f, 0, 1.0f))));
					geometry::moveAbs(a, -10.0f, 0, 10.0f); // move to <-10,0,10>
					geometry::transform(a, geometry::rotationMatrix(F_PI / 2.0f, Z_AXIS));
					REQUIRE(vectorEqual(a.surfaceGeometry->getWorldOrigin(), geometry::point(0.0f, -10.0f, 10.0f)));
					REQUIRE(vectorEqual(a.surfaceGeometry->getWorldDirection(), glm::normalize(geometry::vector(0.0f, 1.0f, -1.0f))));
					REQUIRE(vectorEqual(a.surfaceGeometry->getWorldOrientation(), glm::normalize(geometry::vector(0.0f, 1.0f, 1.0f))));
				}
			}
		}
	}
	
	GIVEN("A vector of actor objects")
	{
		THEN("The IDS of all the actors should be unique and incrementing")
		{
			//Make a vector of 100 actors
			std::vector<actor::Actor> actors(100);
			auto testPassed = true;
			auto expectedID = actors[0].id;
			for (auto const& member : actors)
			{
				testPassed &= (member.id == expectedID);
				expectedID++;
				if (!testPassed) std::cout << member.id << std::endl;
			}
			REQUIRE(testPassed);
		}
	}
}