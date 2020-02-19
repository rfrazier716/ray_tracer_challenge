#include "tracer/geometry/surfaces/surfsphere.hpp"
#include "tracer/geometry/primitives.hpp" 
#include "tracer/geometry/transforms.hpp"

#include "catch.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/epsilon.hpp"

#include <memory> // for smart pointers
#include <vector> // to use std::vector
#include <iostream>

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

SCENARIO("Creating and probing a Sphere Object", "[SphericalSurface]")
{
	GIVEN("A new SphericalSurface Object")
	{
		auto sphereA = std::make_unique<geometry::SphericalSurface>(); // create a new sphere object
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
					if (std::abs(glm::length(geometry::toVector(sphereRadius)) - 1.0f) > FLT_EPSILON)
					{
						sphereRadiusCorrect = false;
					}
				}
			}
			REQUIRE(sphereRadiusCorrect);
		}

	}
}
SCENARIO("Applying Transforms to a Sphere", "[SphericalSurface]")
{
	GIVEN("A unit Sphere Object")
	{
		auto sphere = std::make_unique<geometry::SphericalSurface>();
		THEN("The sphere's coordinates a (0,0) is (0,0,1)")
		{
			REQUIRE(vectorEqual(sphere->sample(0, 0), geometry::point(0, 0, 1.0f)));
			AND_THEN("Scaling the Sphere moves the point")
			{
				geometry::transform(*sphere, geometry::scaleMatrix(1, 1, 10.0f));
				REQUIRE(vectorEqual(sphere->sample(0, 0), geometry::point(0, 0, 10.0f)));
				REQUIRE(vectorEqual(sphere->sample(0.5, 0), geometry::point(1.0f, 0, 0)));
			}
			AND_THEN("Moving the sphere moves the point")
			{
				sphere->setWorldTransform(glm::mat4(1.0f)); // reset the sphere's transforms
				geometry::transform(*sphere, geometry::translationMatrix(1.0f));
				REQUIRE(vectorEqual(sphere->sample(0, 0), geometry::point(1.0f, 1.0f, 2.0f)));
				REQUIRE(vectorEqual(sphere->sample(1.0f, 0), geometry::point(1.0f, 1.0f, 0.0f)));
			}
		}
	}
}
SCENARIO("Verifying Ray Sphere intersections", "[SphericalSurface]")
{
	GIVEN("A ray at the (-10,0,0) pointing towards (1,0,0) and a unit sphere") 
	{
		auto ray = geometry::Ray{ 
			geometry::point(-10, 0, 0), 
			geometry::vector(1, 0, 0) };
		auto sphere = std::make_unique<geometry::SphericalSurface>(); // declare a new sphere on the heap
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
		auto sphere = std::make_unique<geometry::SphericalSurface>(); // declare a new sphere on the heap
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
		auto sphere = std::make_unique<geometry::SphericalSurface>(); // declare a new sphere on the heap
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
		auto sphere = std::make_unique<geometry::SphericalSurface>();
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
SCENARIO("Verifying Sphere Normals","[SphericalSurface]")
{
	GIVEN("A Unit Sphere")
	{
		auto sphere = std::make_unique<geometry::SphericalSurface>();
		THEN("The normal at u=0 is <0,0,1>")
		{
			REQUIRE(vectorEqual(sphere->normal(0, 0), geometry::vector(0, 0, 1.0f)));
			AND_THEN("the normal at u=1.0f is <0,0,-1.0f>")
			{
				REQUIRE(vectorEqual(sphere->normal(1.0f, 0), geometry::vector(0, 0, -1.0f)));
			}
		}
		THEN("The normal at any point on the unmodified sphere is simply the coordinate on the sphere")
		{
			auto sphereNormalsValidated = true;
			for (float u = 0; u <= 1.0f; u += 0.1f)
			{
				for (float v = 0; v <= 1.0f; v += 0.1f)
				{
					auto norm = sphere->normal(u, v);
					auto coord = geometry::toVector(sphere->sample(u, v));
					if (!vectorEqual(norm, coord))
					{
						sphereNormalsValidated = false;
						logVector(norm);
						logVector(coord);
					}
				}
			}
			REQUIRE(sphereNormalsValidated);
		}
		AND_THEN("We scale the sphere to be zero in the Z direction")
		{
			geometry::transform(*sphere, geometry::scaleMatrix(1, 1, 0.0f));
			THEN("The normals from u=[0,0.5) should be <0,0,1>")
			{
				auto sphereNormalsValidated = true;
				for (float u = 0; u <0.5f; u += 0.1f)
				{
					for (float v = 0; v <= 1.0f; v += 0.1f)
					{
						auto norm = sphere->normal(u, v);
						if (!vectorEqual(norm, geometry::vector(0,0,1)))
						{
							sphereNormalsValidated = false;
							logVector(norm);
						}
					}
				}
				REQUIRE(sphereNormalsValidated);
			}
			THEN("The normals from u=(0.5,1] should be <0,0,-1>")
			{
				auto sphereNormalsValidated = true;
				for (float u = 0.51f; u <=1.0f; u += 0.1f)
				{
					for (float v = 0; v <= 1.0f; v += 0.1f)
					{
						auto norm = sphere->normal(u, v);
						if (!vectorEqual(norm, geometry::vector(0, 0, -1)))
						{
							sphereNormalsValidated = false;
							logVector(norm);
						}
					}
				}
				REQUIRE(sphereNormalsValidated);
			}
		}
	}
}