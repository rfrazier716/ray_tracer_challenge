#include "tracer/geometry/surfaces/uvsurface.hpp"

using namespace tracer;

void geometry::UVSurface::setWorldTransform(glm::mat4 const& transform) //!< sets the world transform matrix, will overwrite the current matrix
{
    toWorldSpaceTMat = transform;
    updateInverseTransform = true; //setter to tell object that it needs to modify it's inverse matrix
}

glm::mat4 geometry::UVSurface::getObjectTransform() //!< returns the value of the object space transform matrix 
{
    //recalculate the inverse matrix if the main transform has been updated since this was last called
    if (updateInverseTransform)
    {
        //assert that the matrix is invertible
        assert(glm::determinant(toWorldSpaceTMat) != 0.0f || !(std::cerr << "World Transform Matrix is non-invertable" << std::endl));
        fromWorldSpaceTMat = glm::inverse(toWorldSpaceTMat);
    }
    return fromWorldSpaceTMat;
}
