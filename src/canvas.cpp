#include <memory> //for shared pointers
#include <glm/vec3.hpp>

template <class T>
class Canvas
{
private:
	T* canvas; // make a data array to hold RGB values
public:
	const int rows, columns; //these are the rows and columns of the canvas
	Canvas() : columns(HRES), rows(VRES)
	{
		canvas = new T[rows][columns];
	}
	~Canvas()
	{
		delete canvas
	}

};
