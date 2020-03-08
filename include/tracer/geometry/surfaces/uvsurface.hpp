#pragma once //Only execute once
#define GLM_FORCE_SWIZZLE  //include swizzling for this library
#include "glm/mat4x4.hpp" // the 4d matrix tracks the transform from world coordinate space to object coordinate space
#include "glm/vec2.hpp" //used for uv pairs
#include "tracer/geometry/primitives.hpp" //required for points, vectors, and macros
#include "tracer/math.hpp" // includes the c++ standard math library as well as additional functions

#include <assert.h>
#include <iostream>
namespace tracer 
{
    namespace geometry 
    {
        /**
        * A surface that can be sampled anywhere over the interval u=[0,1] and v=[0,1]
        *
        */
        class UVSurface {
        private:
            POINT origin = point(0, 0, 0);
            VECTOR orientation = vector(0, 0, 1);
        protected:
            //Protected variables that the inherited classes will use
            glm::mat4 toWorldSpaceTMat = glm::mat4(1.0); //!< The transform matrix from object space to world space
            glm::mat4 fromWorldSpaceTMat = glm::mat4(1.0); //!< The transform matrix from object space to world space
            bool updateInverseTransform = false; //!< Whether or ne the world space transform needs to be updated
            float uMin = 0;
            float uMax = 1.0f;
            float vMin = 0;
            float vMax = 1.0f;

        public:
            void setWorldTransform(glm::mat4 const& transform);
            glm::mat4 getWorldTransform() { return toWorldSpaceTMat; } //!< returns the value of the world transform matrix
            glm::mat4 getObjectTransform();
            POINT getWorldOrigin() { return origin; }//!< returns the object origin in world space
            VECTOR getWorldOrientation() { return orientation; }

            virtual POINT sample(float u, float v) { return point(0, 0, 0); } //!<returns the cartesian coordinate of the surface at the specificed u,v coordinate
            virtual POINT sample(glm::vec2 uv) { return point(0, 0, 0); }

            virtual VECTOR normal(float u, float v) { return vector(0, 0, 0); } //!< returns the unit normal vector of the sphere at coordinate u,v
            virtual VECTOR normal(glm::vec2 uv) { return vector(0, 0, 0); }

            virtual VECTOR tangent(float u, float v) { return vector(0, 0, 0); } //!< returns the unit tangent bector of the sphere at coordinate u,v
            virtual VECTOR tangent(glm::vec2 uv) { return vector(0, 0, 0); }

            /**
            * /brief find the intersections between the surface and the ray
            *   The returned value is the number of intersections, each intersection will be inserted into the intersections array passed as an argument
            *
            */
            virtual int findIntersections(Ray ray, Intersection* intersections) { return 0; }
        };

        typedef std::unique_ptr<geometry::UVSurface> pUVSurface;

        /**
         * \class SphericalSurface
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
        class SphericalSurface : public UVSurface
        {
        private:
            glm::vec2 uvFromPoint(float x, float y, float z); //!< returns the uv coordinate of the unit sphere, throws an error if coordinate does not exist on sphere
            glm::vec2 uvFromPoint(glm::vec4 point);
        public:
            POINT sample(float u, float v); //!<returns the cartesian coordinate of the sphere at the specificed u,v coordinate
            VECTOR normal(float u, float v); //!< returns the unit normal vector of the sphere at coordinate u,v
            /**
            * /brief find the intersections between a ray object and the sphere
            *
            * the ray and a pointer to the intersection array is passed as function arguments.
            * The return argument is an int with how many intersections occured
            * The ray that is passed should be represented in the world coordinate space, locally the function will transform it into object space
            *
            * possible outcomes are:
            * 0 intersections - the intersection array is not modified, the function returns false;
            * 1 intersection - the ray is a tangent line to the sphere, both values of the intersection array return the same value
            * 2 intersections - the ray passes through the sphere at a point that is not tangent to the surface, returns two distinct values
            *
            */
            int findIntersections(Ray ray, Intersection* intersections);
        };

        class PointSurface : public UVSurface
        {
        public:
            POINT sample(float u, float v) { return getWorldOrigin();} //!<A point sampled anywhere is just the point's origin
            VECTOR normal(float u, float v) { return geometry::vector(0, 0, 1); } //!< Technically a point has no normal so return z-hat
            /**
            * /brief find the intersections between a ray object and the point
            *
            * the ray and a pointer to the intersection array is passed as function arguments.
            * The return argument is an int with how many intersections occured
            * The ray that is passed should be represented in the world coordinate space, locally the function will transform it into object space
            *
            * possible outcomes are:
            * 0 intersections - the intersection array is not modified, the function returns false;
            * 1 intersection - the ray hits the point
            * 
            */
            int findIntersections(Ray ray, Intersection* intersections);
        };
    }
}