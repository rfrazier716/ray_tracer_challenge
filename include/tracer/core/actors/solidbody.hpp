#pragma once
#include "tracer/geometry/primitives.hpp"
#include "tracer/geometry/surfaces/uvsurface.hpp"
#include "tracer/geometry/transforms.hpp"
#include "tracer/core/material.hpp"

#include <memory>



namespace tracer
{
    namespace actor
    {
        /*
        * A solid body is the base class for
        *
        */
        typedef
        class SolidBody
        {
        protected:
            PhongMaterial material; //!< Material property of the body, determines color etc. 
        public:
            std::unique_ptr<geometry::UVSurface> geometry; //!< The surface geometry of the solid body, used for intersections and transform    
            PhongMaterial getMaterial() { return material; }
        } SolidBody,*solidBodyPtr;

        class UVSphere : public SolidBody
        {
        public:
            UVSphere() { geometry = std::make_unique<geometry::SphericalSurface>(); } //make geometry point to a Spherical Surface
        };
    }
}