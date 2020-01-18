#pragma once

#include "glm/vec3.hpp" //The color values for the canvas are really just 3D vectors 
#include "tracer/colors.hpp"
#include <fstream>
#include <algorithm>  

enum ExportFormat { ppm, jpg, png }; //supported export formats

class Canvas
{
private:
	
	COLOR* canvas; // Pointer to the canvas array that will hold all data
	int canvasIndex(int x, int y) { return y * width + x; } //returns the 1d memory offset for canvas based on row-value pair

	int exportPPM(); //Exports the canvas to a ppm file

public:
	const int width, height; // The dimensions of our canvas, in pixels


	Canvas(int width, int height); // Class Constructor
	~Canvas();	// Destructor

	void writePixel(int row, int column, glm::vec3 color); // function used to write a pixel to the canvas
	COLOR getPixel(int row, int column); //returns color of the canvas at that pixel value
	void blank(); //blanks the canvas to all black
	int generateImage(ExportFormat format = ppm);
};