#include "tracer/core/actors/solidbody.hpp"
#include "tracer/geometry/transforms.hpp"
#include "tracer/math.hpp"

#include "catch.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/epsilon.hpp"

using namespace tracer;
typedef std::unique_ptr<actor::SolidBody> solidBodyPtr;
SCENARIO("Creating and probing a UVSphere", "[Object]")
{
	GIVEN("A new Sphere instance")
	{
		auto sphere = actor::UVSphere();
		THEN("The Sphere Material should be the default Phong Shader")
		{
			REQUIRE(sphere.getMaterial().color == WHITE);
			REQUIRE(sphere.getMaterial().ambient == 0.10f);
			REQUIRE(sphere.getMaterial().diffuse == 1.0f);
			REQUIRE(sphere.getMaterial().specular == 1.0f);
			REQUIRE(sphere.getMaterial().shininess == 200.0f);
		}
		THEN("The sphere's geometry functions should be accessable")
		{
			REQUIRE(vectorEqual(geometry::vector(0, 0, 1.0f), sphere.geometry->normal(0, 0)));
		}
		THEN("Applying a transform to the sphere properly transforms the geometry")
		{
			geometry::transform(*(sphere.geometry), geometry::scaleMatrix(10.0f)); //Scale the sphere by 10 in XYZ
			REQUIRE(vectorEqual(sphere.geometry->sample(0, 0),geometry::point(0, 0, 10.0f)));
		}

	}
}
SCENARIO("Creating a Vectore of SolidBodyPointers")
{
	GIVEN("a Std::vector of solidbody pointers along the x-Axis")
	{
		auto nSpheres = 10;
		std::vector<solidBodyPtr> bodies;
		bodies.reserve(nSpheres);
		// the [] is a lambda expression
		std::generate_n(std::back_inserter(bodies), nSpheres, [] { return std::make_unique<actor::UVSphere>(); });
		THEN("Iterating over the vector should be able to update the location of each body")
		{
			auto testPassed = true;
			for (unsigned int i = 0; i < bodies.size(); i++)
			{
				geometry::transform(*(bodies[i]->geometry), geometry::translationMatrix((float)i, 0, 0));
				if (bodies[i]->geometry->getWorldOrigin()[0] != i) testPassed = false;
			}
		}
	}
}