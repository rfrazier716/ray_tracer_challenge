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

void Canvas::writePixel(int x, int y, COLOR color)
{
	// function used to write a pixel to the canvas
	// because this is a 1D chunk of memory need to do the row column mask by ourself
	canvas[canvasIndex(x,y)] = color;
}

COLOR Canvas::getPixel(int x, int y)
{
	//return the color value of a pixel on the canvas
	return canvas[canvasIndex(x, y)];
}

void Canvas::blank()
{
	//set every pixel value to black
	for (int j = 0; j < width * height; j++)
	{
		canvas[j] = BLACK;
	}
}

//Export functions
int Canvas::exportPPM()
{
	std::ofstream imageFile;
	imageFile.open("image.ppm"); //open a ppm file
	//TODO: Add a guard in case the stream cannot open the file
	if (imageFile.is_open()) //if the file opened successfully
	{
		imageFile << "P3\n"; //Tells system what version of ppm is being used
		imageFile << int(width) << " " << int(height) << "\n" << "255" << "\n"; // the width and height of the image and max value for our numbers
		int newLineCounter = 0; //this determines how often to write a newline
		//iterate through every pixel and export as an int 
		for (int j = 0; j < width * height; j++)
		{
			COLOR* pixel = &canvas[j]; //pointer to the current pixel
			imageFile << std::clamp(int(255 * pixel->r),0,255) << " "; //write the R value
			imageFile << std::clamp(int(255 * pixel->g), 0, 255) << " "; //write the G value
			imageFile << std::clamp(int(255 * pixel->b), 0, 255) << " "; //write the B value
			newLineCounter++; //incrememt the char counter
			if (newLineCounter >= 5)
			{
				//If we written the max number of characters allowed (in theory 12*5 because limit is 60 lines)
				newLineCounter = 0;
				imageFile << std::endl;
			}
		}
		imageFile.close(); // close the file
		return 0; // return that no error happened
	}
	else
	{
		//If it did not open properly return a -1
		return -1;
	}

}

int Canvas::generateImage(ExportFormat format)
{
	switch (format)
	{
	case ppm:
		exportPPM();
		break;
	default: 
		// if no format is picked return a -1 which means an error occured
		return -1;
	}
}