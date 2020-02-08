#pragma once //Only execute once
#include "glm/mat4x4.hpp" // the 4d matrix tracks the transform from world coordinate space to object coordinate space
#include "tracer/geometry/primitives.hpp" //required for points, vectors, and macros
#include "tracer/math.hpp" // includes the c++ standard math library as well as additional functions

/**
 * \class Sphere
 *
 *
 * \brief A spherical surface class, assumes the origin of the sphere is at <0,0,0> and it has a radius of 1
 *
 * the sphere is defined by two parameters u and v over the range [0,1] for both variables, where the traditional
 * spherical coordinates theta and phi are:
 * 
 * theta = pi*u 
 * phi = 2 * pi * v
 *
 * The sphere is a unit sphere centered at the origin in object space, all world space transforms are applied in the 4x4 worldTransformMatrix
 * To do a ray trace, transform the ray from world space to object space and find the intersection
 */

namespace tracer{
	namespace geometry {
		class Sphere {
		private:
            glm::mat4 toWorldSpaceTMat = glm::mat4(1.0); //!< The transform matrix from object space to world space
		public:
            POINT sample(float u, float v); //!<returns the cartesian coordinate of the sphere at the specificed u,v coordinate
            VECTOR normal(float u, float v); //!< returns the unit normal vector of the sphere at coordinate u,v
            VECTOR tangent(float u, float v); //!< returns the unit tangent bector of the sphere at coordinate u,v

            void setWorldTransform(glm::mat4& transform); //!< sets the world transform matrix, will overwrite the current matrix
            glm::mat4 getWorldTransform(); //!< returns the value of the world transform matrix
            glm::mat4 getObjectTransform(); //!< returns the value of the object space transform matrix 
		};
	}
}