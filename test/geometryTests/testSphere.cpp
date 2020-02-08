#include "tracer/geometry/sphere.hpp"
#include "tracer/geometry/primitives.hpp" 

#include "catch.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/epsilon.hpp"

#include <memory> // for smart pointers
#include <vector> // to use std::vector

using namespace tracer;

SCENARIO("Creating and probing a Sphere Object", "[Sphere]")
{
	GIVEN("A new Sphere Object")
	{
		auto sphereA = std::make_unique<geometry::Sphere>(); // create a new sphere object
		THEN("the value of the sphere at u=v=0 should be the point (0,0,1)")
		{
			REQUIRE(vectorEqual(sphereA->sample(0, 0), geometry::point(0, 0, 1)));
			AND_THEN("The normal of the sphere at u=v=0 should be the vector <0,0,1>")
			{
				REQUIRE(vectorEqual(sphereA->normal(0, 0), geometry::vector(0, 0, 1)));
			}
		}
		THEN("If u<0.5, regardless of the value of v, z should be >0")
		{
			auto uMappingFunctional = true;
			for (float u = 0; u < 50; u++)
			{
				for (float v = 0; v < 100.; v++)
				{
					if (sphereA->sample(u / 100.0f, v / 100.0f).z < 0)
					{
						uMappingFunctional = false;
					}
				}
			}
			REQUIRE(uMappingFunctional);
		}
		THEN("if u=0.5, regardless of the value of v z should be 0")
		{
			auto uMappingFunctional = true;
			auto u = 0.5;
			for (float v = 0; v < 100.; v++)
			{
				if (std::abs(sphereA->sample(u , v / 100.0f).z-0)>FLT_EPSILON)
				{
					uMappingFunctional = false;
				}
			}
		}
		THEN("if v=[0,0.25,0.5,1] and u=0.5 the xy pairs should be [(0,1,0),(1,0,0),(0,-1,0),(-1,0,0)]")
		{
			auto vMappingFunctional = true;
			auto u = 0.5f;
			float vVals[] = { 0, 0.25, 0.5, 1.0 };
			POINT expectedPoints[] = {
				geometry::point(0,1,0),
				geometry::point(1,0,0),
				geometry::point(0,-1,0),
				geometry::point(-1,0,0)
			};
			for (int j=0;j<1;j++)
			{
				if (!vectorEqual(expectedPoints[j], sphereA->sample(u,vVals[j])))
				{
					//if the expected point is not the sampled point the test failed
					vMappingFunctional = false;
				}
			}
			REQUIRE(vMappingFunctional);
		}
		THEN("Every point on the sphere should have a magnitude of 1")
		{
			auto sphereRadiusCorrect = true;
			for (int u = 0; u <= 100; u++)
			{
				for (int v = 0; v <= 100; v++)
				{
					auto sphereRadius = sphereA->sample(u / 100.0f, v / 100.0f);
					geometry::toVector(sphereRadius); // convert to a vector
					if (std::abs(glm::length(sphereRadius) - 1.0f) > FLT_EPSILON)
					{
						sphereRadiusCorrect = false;
					}
				}
			}
			REQUIRE(sphereRadiusCorrect);
		}
	}
}