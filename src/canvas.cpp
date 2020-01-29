#include "tracer/canvas.hpp" //Definition of the canvas class

#include <sstream> //this is used by the helper functions so not defined in the header

//Helper functions
glm::uvec3 uint8Color(COLOR &floatColor)
{

	auto uintColor = glm::uvec3(); //make an int type glm vector
	//convert the values between zero and 255
	uintColor.r = std::clamp(int(255 * floatColor.r), 0, 255);
	uintColor.g = std::clamp(int(255 * floatColor.g), 0, 255);
	uintColor.b = std::clamp(int(255 * floatColor.b), 0, 255);
	return uintColor; //return the color as an int
}

std::string ppmStringFromPixel(COLOR &pixel)
{
	glm::ivec3 uint8Pixel = uint8Color(pixel); //convert the pixel as a 0-255 range
	std::stringstream ss; // make a string string to push the values onto
	// write the rgb values onto the string stream
	ss << uint8Pixel.r << ' ';
	ss << uint8Pixel.g << ' ';
	ss << uint8Pixel.b << ' ';
	//return a string of the object
	return ss.str();
}

void pixelToPPMFile(std::ofstream &stream, COLOR& pixel)
{
	glm::uvec3 uint8Pixel = uint8Color(pixel); //convert the pixel as a 0-255 range
	std::stringstream ss; // make a string string to push the values onto
	// write the rgb values onto the string stream
	stream << uint8Pixel.r << ' ';
	stream << uint8Pixel.g << ' ';
	stream << uint8Pixel.b << ' ';
}

/*
COLOR pixelFromPPMString(std::string ppmString)
{
	//Make a function that scans in ppm string values and returns a COLOR
	return COLOR RED;
}
*/

Canvas::Canvas(int width, int height) : width(width), height(height)
{
	canvas = new COLOR[height*width]; // this is the actual canvas that stores pixel values
	blank(); //set all pixel values to zero
}

Canvas::~Canvas()	// Destructor
{
	delete canvas; //delete the memory from the heap
}

int Canvas::canvasIndex(int x, int y)
{
	//Throw an exception if they try to access bad memory
	if (x<0 || y<0 || x>=width || y>=height)
	{
		throw std::out_of_range("Indexing outside of canvas range");
	}
	return y * width + x;
}

COLOR Canvas::getPixel(int x, int y)
{
	//return the color value of a pixel on the canvas
	return canvas[canvasIndex(x, y)];
}

void Canvas::writePixel(int x, int y, COLOR color)
{
	//return the color value of a pixel on the canvas
	canvas[canvasIndex(x, y)]=color;
}


void Canvas::writeCartesian(float x, float y, COLOR color)
{
	int xPx = width / 2 + x; 
	int yPx = height / 2 - y;
	canvas[canvasIndex(xPx, yPx)] = color;
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
			pixelToPPMFile(imageFile,canvas[j]);
			if (newLineCounter > 5)
			{
				//if the next pixel would make the line more than 70 character, add a newline
				newLineCounter = 0;
				imageFile << std::endl;
			}
			newLineCounter++;
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
int Canvas::exportBMP()
{
	std::ofstream imageFile;
	imageFile.open("image.bmp",std::ios::out|std::ios::binary); //make a new binary file to write to
	if (imageFile.is_open())
	{
		BMPSTANDARDHEADER stdHeader(width, height); //The standard header file for BMP images
		BMPINFOHEADER infoHeader(width, height); //The Info Header file for BMP Images
		int bytesPerPixel = infoHeader.biBitCount / 8; //will nominally be 3 for 24 bit data
		int paddingSize = 4-((bytesPerPixel * width) % 4); //this is how many padding bytes we have to write at the end of each row to make it a multiple of 4
		paddingSize = paddingSize == 4 ? 0 : paddingSize; //if the padding size is 4 it should actually be zero
		char* paddingArray = new char[paddingSize]; //make a new padding array on the heap
		for (int j = 0; j < paddingSize; j++) paddingArray[j] = '\0'; //Set it's values to 0x00

		//write headers to file
		imageFile.write(stdHeader.header,2*BMP_STDHEADERSIZE);
		imageFile.write(infoHeader.header, 2 * BMP_INFOHEADERSIZE);
		//write each pixel to file
		for (int h = height - 1; h >= 0; h--)
		{
			//Write the row of pixels from bottom up
			for (int w = 0; w < width; w++)
			{
				auto uintPixel = uint8Color(canvas[h*width+w]); //the the pixel value as an unsigned int;
				char pixelArray[3]; //a char array to hold the pixel values
				//load the char array with the pixel values
				pixelArray[0] = (char)uintPixel.b;
				pixelArray[1] = (char)uintPixel.g;
				pixelArray[2] = (char)uintPixel.r;
				imageFile.write(pixelArray, 3);
			}
			imageFile.write(paddingArray, paddingSize); //write the pad bits
		}
		imageFile.close();
		delete [] paddingArray;
		return 0;
	}
	else
	{
		return -1;
	}
}
int Canvas::generateImage(ExportFormat format)
{
	switch (format)
	{
	case ExportFormat::ppm:
		return exportPPM();
	case ExportFormat::bmp:
		return exportBMP();
	default: 
		// if no format is picked return a -1 which means an error occured
		return -1;
	}
}