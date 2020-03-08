#pragma once
#include "tracer/core/actors/actor.hpp"
#include "tracer/core/material.hpp"

#include <memory>

namespace tracer
{
    namespace actor
    {
        class SolidBody : public Actor
        {
        protected:
            PhongMaterial material; //!< Material property of the body, determines color etc. 
        public:
            PhongMaterial getMaterial() { return material; }
        };

        typedef std::unique_ptr<SolidBody> pSolidBody;
        typedef std::shared_ptr<SolidBody> pSSolidBody;

        class UVSphere : public SolidBody
        {
        public:
            UVSphere() { surfaceGeometry = std::make_unique<geometry::SphericalSurface>(); } //make geometry point to a Spherical Surface
        };
    }
}