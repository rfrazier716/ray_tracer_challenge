#include "tracer/canvas.hpp" //Definition of the canvas class

Canvas::Canvas(int width, int height) : width(width), height(height)
{
	canvas = new COLOR[height*width]; // this is the actual canvas that stores pixel values
	blank(); //set all pixel values to zero
}

Canvas::~Canvas()	// Destructor
{
	delete canvas; //delete the memory from the heap
}

void Canvas::writePixel(int row, int column, COLOR color)
{
	// function used to write a pixel to the canvas
	// because this is a 1D chunk of memory need to do the row column mask by ourself
	canvas[canvasIndex(row,column)] = color;
}

COLOR Canvas::getPixel(int row, int column)
{
	//return the color value of a pixel on the canvas
	return canvas[canvasIndex(row, column)];
}

void Canvas::blank()
{
	//set every pixel value to black
	for (int j = 0; j < width * height; j++)
	{
		canvas[j] = BLACK;
	}
}

int Canvas::generateImage(fs::path exportPath, char* format = "ppm")
{
	return 0;
}