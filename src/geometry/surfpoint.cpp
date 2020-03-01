#include "tracer/geometry/surfaces/uvsurface.hpp"
using namespace tracer;

    POINT geometry::PointSurface::sample(float u, float v); //!<returns the cartesian coordinate of the sphere at the specificed u,v coordinate
    //POINT sample(glm::vec2 uv);

    VECTOR geometry::PointSurface::normal(float u, float v); //!< returns the unit normal vector of the sphere at coordinate u,v
    //VECTOR normal(glm::vec2 uv);

    VECTOR geometry::PointSurface::tangent(float u, float v); //!< returns the unit tangent bector of the sphere at coordinate u,v
    //VECTOR tangent(glm::vec2 uv);

    void geometry::PointSurface::setWorldTransform(glm::mat4 const& transform); //!< sets the world transform matrix, will overwrite the current matrix
    glm::mat4 geometry::PointSurface::getWorldTransform(); //!< returns the value of the world transform matrix
    glm::mat4 geometry::PointSurface::getObjectTransform(); //!< returns the value of the object space transform matrix

    int geometry::PointSurface::findIntersections(Ray ray, Intersection* intersections);
};