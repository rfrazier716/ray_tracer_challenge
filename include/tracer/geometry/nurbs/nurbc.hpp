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
#include "glm/vec4.hpp" //this is also included in primitives but added just to be safe

namespace tracer //use tracer namespace for ray tracer functions 
{
	namespace geometry
	{
		class NURBC //a nurbs contour that can exist in three dimensions but has on sampling parameter (t) defined on t->[0,1]
		{
		private:
			bool clampedAtStart=true; // whether the curved is clamped to the first control point, if so the first degree + 1 points will be set to zero
			bool clampedAtEnd=true; // whether the curve is clamped to the last control point, if so the last degree + 1 points will be set to zero

			//knots, control points and weight are defined as std::vector so they can be expanded on the fly
			std::vector<float> knots; //knot vector
			std::vector<glm::vec4> controlPoints; //control points
			std::vector<float> weights; // weight vector

			const int degree; // degree is a constant and cannot be changed without creating a new object
		
		public:


			NURBC(int); //generator function
			
			int nCPoints(); // returns the number of control points
			int nKnots(); //returns the size of the knot vector
			
			glm::vec4 getPoint(int);
			void setPoint(int, glm::vec4);

			float getWeight(int);
			void setWeight(int, float);

			float getKnot(int);
			void setKnot(int, float);

			void clampStart();
			void clampEnd();
			void freeStart();
			void freeEnd();
		};
	}
}
