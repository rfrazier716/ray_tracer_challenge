#include <iostream>
#include "catch.hpp"
#include "glm/glm.hpp"
#include <memory>

typedef std::unique_ptr<glm::mat4> matPtr4d;

SCENARIO("Constructing and Inspecting a 4x4 Matrix", "[matrices]")
{
    GIVEN("Creating a 4x4 Matrix with the following values ")
    {
        std::unique_ptr<int> test (new int(35));
        matPtr4d testMatrix (new glm::mat4(
            1.0,2.0,3.0,4.0,
            5.5,6.5,7.5,8.5,
            9.0,10.0,11.0,12.0
            ,13.5,14.5,15.5,16.5));
    }
}