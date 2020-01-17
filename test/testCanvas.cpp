#include <iostream>
#include "catch.hpp"
#include "glm/glm.hpp"
#include "tracer/canvas.hpp"

#define COLOR glm::ivec3
#define RED COLOR(1,0,0)
#define GREEN COLOR(0,1,0)
#define BLUE COLOR(0,0,1)

SCENARIO("Creating a Canvas", "[canvas]")
{
    GIVEN("Create a new canvas with width of 10 and height of 20")
    {
        std::shared_ptr<Canvas> canvas = std::make_shared<Canvas>(10, 20); // make a new canvas
        THEN("Width of canvas is  10, Height is 20")
        {
            REQUIRE(canvas->width == 10);
            REQUIRE(canvas->height == 20);
            AND_THEN("Every color defaults to (0,0,0)")
            {
                bool allCellsZero = true;
                for (int w = 0; w < canvas->width; w++)
                {
                    for (int h = 0; h < canvas->height; h++)
                    {
                        if (!glm::all(glm::equal(canvas->getPixel(h, w), glm::ivec3(0, 0, 0))))
                        {
                            allCellsZero = false;
                        }
                    }
                }
                REQUIRE(allCellsZero);

            }

        }
    }
    GIVEN("Create a new canvas with width of 10 and height of 20")
    {
        std::shared_ptr<Canvas> canvas = std::make_shared<Canvas>(10, 20); // make a new canvas
        WHEN("We write red to a pixel in location 2,3")
        {
            canvas->writePixel(2, 3, RED);
            THEN("That pixels value is (1,0,0)")
            {
                REQUIRE(glm::all(glm::equal(canvas->getPixel(2, 3), RED)));
            }
        }
    }
}

SCENARIO("Writing to Canvas", "[canvas]")
{
    GIVEN("Create a new canvas with width of 10 and height of 20")
    {
        std::shared_ptr<Canvas> canvas = std::make_shared<Canvas>(10, 20); // make a new canvas
        WHEN("We write red to a pixel in location 2,3")
        {
            canvas->writePixel(2, 3, RED);
            THEN("That pixels value is (1,0,0)")
            {
                REQUIRE(glm::all(glm::equal(canvas->getPixel(2, 3), RED)));
            }
        }
    }
}