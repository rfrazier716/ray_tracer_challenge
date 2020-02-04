
#include "tracer/geometry/nurbs/nurbc.hpp"
#include "catch.hpp"
#include "glm/glm.hpp"

using namespace tracer;
using namespace geometry;

SCENARIO("Constructing and Inspecting a nurbs contour", "[geometry]")
{
	GIVEN("A new nurbs contour of degree 3")
	{
		auto degree = 3;
		auto contour = NURBC(degree);
		THEN("The number of control points is one more than the degree")
		{
			REQUIRE(contour.nCPoints() == degree + 1);
			AND_THEN("Every control point defaults to (0,0,0) and weight defaults to 1.0")
			{
				auto controlDefaultValueValid = true;
				auto weightDefaultValueValid = true;
				for (int j = 0; j < contour.nCPoints(); j++)
				{
					if (!glm::all(glm::equal(contour.getPoint(j), point(0, 0, 0)))) { controlDefaultValueValid = false; }
					if (contour.getWeight(j) != 1.0f) { weightDefaultValueValid = false; }
				}
				REQUIRE(controlDefaultValueValid);
				REQUIRE(weightDefaultValueValid);
			}
		}
		THEN("The number of knots is degree + control points + 1")
		{
			REQUIRE(contour.nKnots() == degree + 1 + contour.nCPoints());
			AND_THEN("The value of knots is zero for the first degree + 1 indices, and 1 for the last degree + 1 indices")
			{
				auto knotsDefaultValueValid = true;
				for (int j = 0; j < contour.nKnots(); j++)
				{
					auto expectedKnotValue = j < degree + 1 ? 0.0f : 1.0f;
					if (contour.getKnot(j) != expectedKnotValue) { knotsDefaultValueValid = false; }
				}
				REQUIRE(knotsDefaultValueValid);
			}
		}
	}
}