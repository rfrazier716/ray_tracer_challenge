/**
 * \class Object
 *
 *
 * \brief Base object that all tracer objects inherit from
 *
 *  has a position in the world coordinate system. To uniquely identify different objects use their pointer values 
 *
 *
 */

#pragma once
#include "tracer/geometry/primitives.hpp"
#include "tracer/core/material.hpp"
#include "tracer/geometry/surfaces/uvsurface.hpp"
#include <memory>

namespace tracer
{
    namespace actor
    {
        /*
        * A solid body is the base class for
        *
        */
        class SolidBody
        {
        protected:
            PhongMaterial material; //!< Material property of the body, determines color etc. 
        public:
            std::unique_ptr<geometry::UVSurface> geometry; //!< The surface geometry of the solid body, used for intersections and transform    
            PhongMaterial getMaterial() { return material; }
        };

        class UVSphere : public SolidBody
        {
        public:
            UVSphere() { geometry = std::make_unique<geometry::SphericalSurface>(); } //make geometry point to a Spherical Surface
        };
    }
}