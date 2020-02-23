/**
 * \class Surface
 *
 *
 * \brief A traceable surface inherited from object
 *
 *  Holds both the surface geometry and miscellaneous values such as color, world coordinate transforms etc. 
 *
 */
#include "tracer/core/material.hpp"
#include "tracer/geometry/surfaces/surphsphere.hpp"

namespace tracer
{
    class Surface
    {
    private:
        phongMaterial material;
        auto surface = geometry::SphericalSurface();
    public:

    };
}