#include "catch.hpp"

#include "glm/vec4.hpp"
#include "tracer/geometry.hpp" //Include the geometry file

TEST_CASE("Points Generate Correctly", "[point]") 
{
    glm::vec4 test_point = point(1.0, 1.5, 2.0);
    REQUIRE(test_point.x == 1.0);
    REQUIRE(test_point.y == 1.5);
    REQUIRE(test_point.z == 2.0);
    REQUIRE(test_point.w == 1.0);
}

TEST_CASE("Vectors Generate Correctly", "[vect]")
{
    glm::vec4 test_vector = vector(1.0, 1.5, 2.0);
    REQUIRE(test_vector.x == 1.0);
    REQUIRE(test_vector.y == 1.5);
    REQUIRE(test_vector.z == 2.0);
    REQUIRE(test_vector.w == 0.0);
}
