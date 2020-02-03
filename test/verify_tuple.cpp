#include <iostream>
#include "catch.hpp"

#include "glm/glm.hpp"
#include "tracer/geometry/primitives.hpp" //Include the geometry file

using namespace tracer;
using namespace geometry;

SCENARIO("Vector Math", "[vectorOps]") 
{
    GIVEN("Have 2 points and two vectors")
    {
        glm::vec4 pointA = point(1.0, 1.0, 1.0);
        glm::vec4 pointB = point(2, 3, 4);
        glm::vec4 vecA = vector(1, 1, 1);
        glm::vec4 vecB = vector(2, 3, 4);
        REQUIRE(pointA.w == 1);
        REQUIRE(pointB.w == 1); // Assert that points have a w of 1
        REQUIRE(vecA.w == 0);
        REQUIRE(vecB.w == 0); // Assert vectors have a w of 0
        WHEN("A vector is compared to itself")
        {
            bool vector_equal = glm::all(glm::equal(vecA, vecA));
            THEN("The vector equality is true ")
            {
                REQUIRE(vector_equal);
            }
        }
        WHEN("Two vectors are added")
        {
            glm::vec4 sum = vecA + vecB;
            THEN("The result is a Vector ")
            {
                REQUIRE(sum.w == 0);
            }
        }
    }
}