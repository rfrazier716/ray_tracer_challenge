#include "tracer/tracer.hpp"
#include "catch.hpp"

using namespace tracer;
SCENARIO("Creating a Renderer", "[Renderers]")
{
	GIVEN("A Renderer object")
	{
		auto r = Renderer(1920, 1080);
		THEN("You can create a Sphere and append it to the bodies")
		{
			auto sphere = std::make_shared<actor::UVSphere>();
			r.addBody(sphere);
			geometry::transform(*sphere, geometry::translationMatrix(3.0f)); //translate the sphere
		}
		THEN("You can create a Point Source and append it to the lights")
		{
			auto lamp = std::make_shared<actor::PointSource>();
			r.addLight(lamp);
		}
		THEN("You can create a camera and set it as the active camera")
		{
			auto camera = std::make_shared<actor::Camera>();
			r.setCamera(camera);
		}
	}
}