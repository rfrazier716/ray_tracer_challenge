#pragma once

#include "glm/vec3.hpp" //The color values for the canvas are really just 3D vectors 
#include "tracer/colors.hpp" //defines color values
#include "tracer/image/bitmap.hpp" // used for BMP Export

#include <fstream>
#include <algorithm>  
#include <string>
#include <stdexcept>

namespace tracer {
	enum class ExportFormat { ppm, bmp }; //supported export formats
	class Canvas
	{
	private:

		COLOR* canvas; // Pointer to the canvas array that will hold all data
		int canvasIndex(int x, int y); //returns the 1d memory offset for canvas based on row-value pair

		int exportBMP(); //Exports the canvas to a bmp file
		int exportPPM(); //Exports the canvas to a ppm file

	public:
		const int width, height; // The dimensions of our canvas, in pixels


		Canvas(int width, int height); // Class Constructor
		~Canvas();	// Destructor

		void writePixel(int row, int column, COLOR color); // function used to write a pixel to the canvas

		/**
		* \brief write pixels to the canvas assuming it spans from [[-width/2,width/2],[-height/2,height/2]] with zero at the center
		*
		* \param x the x coordinate to write to
		* \param y the y coordinate to write to
		* \param color what color value to set the pixel
		*
		*/
		void writeCartesian(float x, float y, COLOR color);
		COLOR getPixel(int row, int column); //returns color of the canvas at that pixel value
		void blank(); //blanks the canvas to all black
		int generateImage(ExportFormat format = ExportFormat::bmp);
	};

	typedef std::unique_ptr<Canvas> pCanvas;
}