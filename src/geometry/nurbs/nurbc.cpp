//will be a class file for nurbs curve and eventually nurbs surface

//what is required: 
// sample along the interval
// when created tell how many control points and degree of curve, this will set the knot vector
// default control points to <0,0,0,1> (point at origin) and knot vector padded appropriately so it is clamped at both ends 
// good addition would creating new control points between original control points but that would require updating the object OR keeping control points in a std::vector
//	which hey, we're not doing matrix math with this, may as well
// once nurbs curves are defined, will need to be able to extend it to a nurbs surface
// Also need to figure out how do to ray-nurbs intersections look at that paper https://www.cs.utah.edu/~shirley/papers/raynurbs.pdf

#include "tracer/geometry/nurbs/nurbc.hpp"

using namespace tracer;
using namespace geometry;

NURBC::NURBC(int degree) : degree(degree)
{
	// length of the control point vector is once more than the degree
	controlPoints.resize(degree + 1);
	weights.resize(degree + 1); //length of the weight vector should be the same as the length of the ctrl points
	knots.resize(2 * degree + 2); // length of the knot vector is degree+control points+1

	// initialize weight vector and control point vector
	for (unsigned int j = 0; j < controlPoints.size(); j++)
	{
		controlPoints[j] = point(0, 0, 0);
		weights[j] = 1;
		knots[j] = 0; // by default the first degree +1 points zero to clamp to the first control point
	}
	for (int j = degree + 1; j < 2 * degree + 2; j++)
	{
		knots[j] = 1; //the last degree + 1 points are 
	}
	
	
}

int NURBC::nCPoints()
{
	return controlPoints.size();
}

int NURBC::nKnots()
{
	return knots.size();
}

glm::vec4 NURBC::getPoint(int index)
{
	return controlPoints.at(index);
}

void NURBC::setPoint(int index, glm::vec4 value)
{
	controlPoints.at(index) = value;
}

float NURBC::getWeight(int index)
{
	return weights.at(index);
}

void NURBC::setWeight(int index, float value)
{
	weights.at(index) = value;
}

float NURBC::getKnot(int index)
{
	return knots.at(index);
}

void NURBC::setKnot(int index, float value)
{
	knots.at(index) = value;
}

void NURBC::clampStart()
{
	clampedAtStart = true; // update clamped at start bool value
	//rewrite first degree + 1 knots to be zero
	for (int j = 0; j < degree + 1; j++)
	{
		knots.at(j) = 0.0f;
	}
}
void NURBC::clampEnd()
{
	clampedAtEnd = true;
	//rewrite last degree + 1 knots to be 1.0f
	for (unsigned int j = knots.size()-(degree + 1); j < knots.size(); j++)
	{
		knots.at(j) = 1.0f;
	}
}
void NURBC::freeStart()
{
	clampedAtStart = false;
}
void NURBC::freeEnd()
{
	clampedAtEnd = false;
}