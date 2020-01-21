#include <iostream>
#include "catch.hpp"
#include "glm/glm.hpp"
#include "tracer/canvas.hpp"
#include "tracer/colors.hpp"



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
                        if (!glm::all(glm::equal(canvas->getPixel(w,h), BLACK)))
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

SCENARIO("Exporting the Canvas", "[canavas]")
{
    GIVEN("Creating a new 5x3 canvas and defining colors")
    {
        std::shared_ptr<Canvas> canvas = std::make_shared<Canvas>(5,3); // make a new canvas
        auto c1 = COLOR(1.5, 0, 0);
        auto c2 = COLOR(0, 0.5, 0);
        auto c3 = COLOR(-0.5, 0, 1.);
        WHEN("We write to the canvas")
        {
            canvas->writePixel(0, 0, c1);
            canvas->writePixel(2, 1, c2);
            canvas->writePixel(4, 2, c3);
            THEN("The files export correctly")
            {
                //REQUIRE(canvas->generateImage(ppm) == 0);
                REQUIRE(canvas->generateImage(bmp) == 0);
            }
        }
    }
}