#include "tracer/geometry/sphere.hpp"
using namespace tracer;

POINT geometry::Sphere::sample(float u, float v){
	// required trig definitions calculated once for speed
	float sinU = std::sin(F_PI * u);
	float cosU = std::cos(F_PI * u);
	float sinV = std::sin(2*F_PI * v);
	float cosV = std::cos(2*F_PI * v);

	float x = sinU * sinV;
	float y = sinU * cosV;
	float z = cosU;
	return point(x, y, z);
}

VECTOR geometry::Sphere::normal(float u, float v){
	auto normalVect = sample(u, v); //sample the sphere at uv to get the point
	toVector(normalVect); //Turn the sphere point into a vector
	return normalVect; //return the vector which points from the origin to the sphere

}

VECTOR geometry::Sphere::tangent(float u, float v){
	return vector(1,1,1); // this function needs to be filled in 
}

void geometry::Sphere::setWorldTransform(glm::mat4& transform) {
	toWorldSpaceTMat = transform;
}

glm::mat4 geometry::Sphere::getWorldTransform() {
	return toWorldSpaceTMat;
}

glm::mat4 geometry::Sphere::getObjectTransform() {
	return glm::inverse(toWorldSpaceTMat);
}
