#include "tracer/geometry/sphere.hpp"
#include "tracer/geometry/primitives.hpp" 
#include "tracer/geometry/transforms.hpp"

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
			auto u = 0.5f;
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
				geometry::point(1,0,0),
				geometry::point(0,1,0),
				geometry::point(-1,0,0),
				geometry::point(0,-1,0)
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
SCENARIO("Verifying Ray Sphere intersections", "[Sphere]")
{
	GIVEN("A ray at the (-10,0,0) pointing towards (1,0,0) and a unit sphere") 
	{
		auto ray = geometry::Ray{ 
			geometry::point(-10, 0, 0), 
			geometry::vector(1, 0, 0) };
		auto sphere = std::make_unique<geometry::Sphere>(); // declare a new sphere on the heap
		THEN("The sphere should intersect the sphere at two points")
		{
			geometry::Intersection hits[2];
			auto nHits = sphere->findIntersections(ray, hits);
			REQUIRE(nHits == 2);
			AND_THEN("The hits should be unique and at t=8 and t=10")
			{
				REQUIRE(hits[0].t != hits[1].t);
				REQUIRE((areSame(hits[0].t,9.0f,FLT_EPSILON) || areSame(hits[0].t, 11.0f,FLT_EPSILON)));
				REQUIRE((areSame(hits[1].t, 9.0f, FLT_EPSILON) || areSame(hits[1].t, 11.0f, FLT_EPSILON)));
			}
		}
	}
	GIVEN("A ray at the (-10,1,0) pointing towards (1,0,0) and a unit sphere")
	{
		auto ray = geometry::Ray{
			geometry::point(-10, 1, 0),
			geometry::vector(1, 0, 0) };
		auto sphere = std::make_unique<geometry::Sphere>(); // declare a new sphere on the heap
		geometry::transform(*sphere, geometry::scaleMatrix(10.0f, 1.0f, 1.0f));
		THEN("The sphere should intersect the sphere at one point")
		{
			geometry::Intersection hits[2];
			auto nHits = sphere->findIntersections(ray, hits);
			REQUIRE(nHits == 1);
			AND_THEN("The hits should be unique and at t=8 and t=10")
			{
				REQUIRE(hits[0].t == hits[1].t);
				REQUIRE(areSame(hits[0].t, 10.0f, FLT_EPSILON));
			}
		}
	}
	GIVEN("A ray at the (-10,1.01,0) pointing towards (1,0,0) and a unit sphere")
	{
		auto ray = geometry::Ray{
			geometry::point(-10, 1.01f, 0),
			geometry::vector(1, 0, 0) };
		auto sphere = std::make_unique<geometry::Sphere>(); // declare a new sphere on the heap
		THEN("The ray should not intersect the sphere")
		{
			geometry::Intersection hits[2];
			auto nHits = sphere->findIntersections(ray, hits);
			REQUIRE(nHits == 0);
		}
	}
	//Edge Cases
	GIVEN("A Ray inside of the sphere at the origin")
	{
		auto sphere = std::make_unique<geometry::Sphere>();
		auto ray = geometry::Ray{
			geometry::point(0,0,0),
			geometry::vector(0.1f,0.2f,0.4f)
		};
		THEN("The ray should intersect the sphere at +/- t")
		{
			geometry::Intersection hits[2];
			auto nHits = sphere->findIntersections(ray, hits);
			REQUIRE(nHits == 2);
			REQUIRE(areSame(hits[0].t + hits[1].t, 0.0f,FLT_EPSILON));
		}
	}
}
