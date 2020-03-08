#include "tracer/tracer.hpp"
#include "testUtils.hpp"
#include "catch.hpp"

using namespace tracer;

SCENARIO("Creating an orthographic Camera", "[OrthoCam]")
{
	GIVEN("An orthographic camera")
	{
		auto camWidth = 2.0f;
		auto aspectRatio = 2; 
		auto pxWidth = 200;
		auto cam = actor::OrthoCamera(camWidth);
		THEN("Getting the ray at (0,0) for a 200x100 frame returns a ray <-1,0.5,0>")
		{
			auto ray = cam.getRay(0, 0, pxWidth, (int)(pxWidth/aspectRatio));
			logVector(ray.position);
			REQUIRE(vectorEqual(ray.position, geometry::point(-camWidth/2, -camWidth/4, 0)));
			REQUIRE(vectorEqual(cam.getRay(pxWidth, 0, pxWidth, (int)(pxWidth / aspectRatio)).position, geometry::point(camWidth/2, -camWidth/4, 0)));
		}
		THEN("Getting a ray at pixel 0->100 for a 100px frame will return a ray from -1 to 1 on 0.02 increments")
		{

		}
	}

}