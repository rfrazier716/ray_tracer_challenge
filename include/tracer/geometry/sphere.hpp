#pragma once //Only execute once
#include "glm/mat4x4.hpp" // the 4d matrix tracks the transform from world coordinate space to object coordinate space
#include "glm/vec2.hpp" //used for uv pairs
#include "tracer/geometry/primitives.hpp" //required for points, vectors, and macros
#include "tracer/math.hpp" // includes the c++ standard math library as well as additional functions

#include <assert.h>
#include <iostream>

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
            glm::mat4 fromWorldSpaceTMat = glm::mat4(1.0); //!< The transform matrix from object space to world space
            glm::vec2 uvFromPoint(float x, float y, float z); //!< returns the uv coordinate of the unit sphere, throws an error if coordinate does not exist on sphere
            glm::vec2 uvFromPoint(glm::vec4 point);
            bool updateInverseTransform = false;

		public:
            POINT sample(float u, float v); //!<returns the cartesian coordinate of the sphere at the specificed u,v coordinate
            POINT sample(glm::vec2 uv);
            
            VECTOR normal(float u, float v); //!< returns the unit normal vector of the sphere at coordinate u,v
            VECTOR normal(glm::vec2 uv);
            
            VECTOR tangent(float u, float v); //!< returns the unit tangent bector of the sphere at coordinate u,v
            VECTOR tangent(glm::vec2 uv);



            void setWorldTransform(glm::mat4& transform); //!< sets the world transform matrix, will overwrite the current matrix
            glm::mat4 getWorldTransform(); //!< returns the value of the world transform matrix
            glm::mat4 getObjectTransform(); //!< returns the value of the object space transform matrix 

            /**
            * /brief find the intersections between a ray object and the sphere
            * 
            * the ray and a pointer to the intersection array is passed as function arguments.
            * The return argument is an int with how many intersections occured
            * 
            * possible outcomes are:
            * 0 intersections - the intersection array is not modified, the function returns false;
            * 1 intersection - the ray is a tangent line to the sphere, both values of the intersection array return the same value
            * 2 intersections - the ray passes through the sphere at a point that is not tangent to the surface, returns two distinct values
            * 
            */
            int findIntersections(Ray ray, Intersection* intersections);
		};
	}
}