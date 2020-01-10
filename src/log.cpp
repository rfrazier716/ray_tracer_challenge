#include <iostream>
#include "tracer/log.hpp"

void log(const char* message)
{
	//print a message onto the console
	std::cout << message << std::endl;
}

void warning(const char* message)
{
	//print a warning to the console
	std::cout << "WARNING: " << message << std::endl;
}