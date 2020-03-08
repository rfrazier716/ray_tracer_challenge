#include "tracer/core/actors/actor.hpp"
#include "catch.hpp"

using namespace tracer;
SCENARIO("Creating an Actor")
{
	GIVEN("A new actor object")
	{
		auto a =actor::Actor();
		THEN("The id of the actor should be 0")
		{
			REQUIRE(a.id == 0);
		}
	}
	
	GIVEN("A vector of actor objects")
	{
		THEN("The IDS of all the actors should be unique and incrementing")
		{
			//Make a vector of 100 actors
			std::vector<actor::Actor> actors(100);
			auto testPassed = true;
			auto expectedID = 1;
			for (auto const& member : actors)
			{
				testPassed &= (member.id == expectedID);
				expectedID++;
			}
			REQUIRE(testPassed);
		}
	}
}