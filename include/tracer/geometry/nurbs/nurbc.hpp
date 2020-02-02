/**
* a nurbs curve that can evaluated along the range t=0:1, will automatically clamp the surface at ends
*
*
*/

#pragma once //only evaluate this code once
#include "geometry/primitives.hpp" //primitives library for points

namespace tracer //use tracer namespace for ray tracer functions 
{
	template<int pts,int degree>
	class nurbc //a nurbs contour that can exist in three dimensions but has on sampling parameter (t) defined on t->[0,1]
	{
	private:
		std::vector 
		//knot vector
		//control points as std::vector
		//degree
	};
}
