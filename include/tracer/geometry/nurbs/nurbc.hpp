/**
 * \class NURBC
 *
 *
 * \brief A nurbs contour 
 *
 *
 *
 */
#pragma once //only evaluate this code once
#include <vector> //required for std::vector
#include "tracer/geometry/primitives.hpp" //primitives library for points

namespace tracer //use tracer namespace for ray tracer functions 
{
	class NURBC //a nurbs contour that can exist in three dimensions but has on sampling parameter (t) defined on t->[0,1]
	{
	private:
		//knots, control points and weight are defined as std::vector so they can be expanded on the fly
		std::vector<float> knots; //knot vector
		std::vector<glm::vec4> controlPoints; //control points
		std::vector<float> weights; // weight vector

		const int degree; // degree is a constant and 

		NURBC(int degree);

	};

}
