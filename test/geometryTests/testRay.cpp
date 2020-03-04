#include "tracer/tracer.hpp" //Include the tracer core library

#include "catch.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/epsilon.hpp"

#include <vector>
#include <memory>
#include <iostream>


using namespace tracer;
typedef std::unique_ptr<actor::SolidBody> solidBodyPtr;

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

SCENARIO("Raycasting into a vector of solidbodies")
{
	GIVEN("a Std::vector of solidbody pointers along the x-Axis")
	{
		auto nSpheres = 10;
		std::vector<solidBodyPtr> bodies;
		bodies.reserve(nSpheres);
		// the [] is a lambda expression
		std::generate_n(std::back_inserter(bodies), nSpheres, [] { return std::make_unique<actor::UVSphere>(); });
		for (unsigned int i = 0; i < bodies.size(); i++)
		{
			geometry::transform(*(bodies[i]->geometry), geometry::translationMatrix(5.0f*i, 0, 0));
		}
		THEN("A ray cast into the bodies should return a group of hits that can be sorted by distance")
		{
			auto ray = geometry::Ray{ geometry::point(-10,0,0),geometry::vector(1,0,0) };
			std::vector<geometry::Intersection> hits;
			hits.reserve(2 * bodies.size()); //a sphere should have at max 2 intersections 
			geometry::Intersection bodyInterX[2];
			for (unsigned int i = 0; i < bodies.size(); i++)
			{
				//iterate over the bodies and fill the intersection array
				auto numHits=bodies[i]->geometry->findIntersections(ray, bodyInterX);
				for (int j = 0; j < numHits; j++)
				{
					hits.push_back(bodyInterX[j]);
				}
			}
		}
	}
}