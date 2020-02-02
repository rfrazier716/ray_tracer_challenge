#include "tracer/canvas.hpp" //canvas handles image transport
#include "tracer/geometry/primitives.hpp" //for points and vectors currently
#include "tracer/colors.hpp" //for colors
#include "tracer/matrixTransforms.hpp" 
#include "tracer/math.hpp"

#include <memory>


//should generate 4 circes of varying radius going red->green->blue->white
int main()
{
	int canvasSize = 250;
	auto canvas = std::make_unique<Canvas>(canvasSize,canvasSize); //create a new canvas object
	float theta = 2 * M_PI / 12;
	auto rotMat = rotationMatrix(-theta, Z_AXIS);
	COLOR colors[] = { RED,GREEN,BLUE,WHITE };
	for (int circNum = 0; circNum < 4; circNum++)
	{
		auto p = point(0, 25 * (circNum + 1), 0); //make a point whos distance from the origin changes
		for (int j = 0; j < 12; j++)
		{
			// Iterate through the 12 hours on a clock
			p = rotMat * p; // rotate the point
			canvas->writeCartesian(p.x, p.y, colors[circNum]); //update the pixel using cartesian update
		}
	}
	canvas->generateImage(); //write the image to a bmp file
}