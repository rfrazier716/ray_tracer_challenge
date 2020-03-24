#include "tracer/tracer.hpp"
#include "testUtils.hpp"
#include "catch.hpp"

using namespace tracer;

SCENARIO("Creating an orthographic Camera", "[OrthoCam]")
{
	GIVEN("An orthographic camera with an aspect ratio of 1.0")
	{
		auto camWidth = 2.0f;
		auto aspectRatio = 2; 
		auto pxWidth = 1000;
		auto pxHeight = 500;
		auto cam = actor::OrthoCamera(camWidth);
		THEN("Getting the ray at the four corners is the camWidth/2")
		{
			auto xPx = 0;
			auto yPx = 0;
			auto generatedRay = cam.getRay(xPx / pxWidth, yPx / pxHeight);
			POINT expectedPositions[] = {
				geometry::point(0,-1,1),
				geometry::point(0,-1,-1),
				geometry::point(0,1,1),
				geometry::point(0,1,-1)
			};
			int j = 0;
			for (float x = 0; x <= 1.0f; x++)
			{
				for (float y = 0; y <= 1.0f; y++)
				{
					auto generatedRay = cam.getRay(x,y);
					REQUIRE(vectorEqual(generatedRay.position,expectedPositions[j]));
					j += 1;
				}
			}
			AND_THEN("Setting the Aspect Ratio correctly maps the rays to the right positions")
			{
				cam.setAspectRatio((float) pxHeight / pxWidth);
				POINT expectedPositions[] = {
					geometry::point(0,-1,0.5f),
					geometry::point(0,-1,-0.5f),
					geometry::point(0,1,0.5f),
					geometry::point(0,1,-0.5f)
				};
				int j = 0;
				for (float x = 0; x <= 1.0f; x++)
				{
					for (float y = 0; y <= 1.0f; y++)
					{
						auto generatedRay = cam.getRay(x, y);
						REQUIRE(vectorEqual(generatedRay.position, expectedPositions[j]));
						j += 1;
					}
				}
			}
		}
	}

}