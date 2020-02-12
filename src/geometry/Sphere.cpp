#include "tracer/geometry/sphere.hpp"
using namespace tracer;

POINT geometry::Sphere::sample(float u, float v){
	// required trig definitions calculated once for speed
	float sinU = std::sin(F_PI * u);
	float cosU = std::cos(F_PI * u);
	float sinV = std::sin(2*F_PI * v);
	float cosV = std::cos(2*F_PI * v);

	float x = sinU * cosV;
	float y = sinU * sinV;
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

glm::vec2 geometry::Sphere::uvFromPoint(float x, float y, float z)
{
	auto point = geometry::point(x, y, z); //put the floats into a point
	return uvFromPoint(point); // call the other UV from point function
}

glm::vec2 geometry::Sphere::uvFromPoint(glm::vec4 point)
{
	//have to subtract 1.0f from the point magnitude because the w component of a point is 1.0
	//assert the point is on the unit sphere
	auto pointMagnitude = glm::dot(point, point) - 1.0f;
	assert(areSame(glm::dot(point,point)-1.0f, 1.0f, FLT_EPSILON) || !(std::cerr << point.x <<","<< point.y << "," << point.z << "," << point.w ));
	auto theta = std::acos(point.z); 
	auto phi = std::atan2(point.y, point.x);
	auto u = theta / F_PI;
	auto v = phi / (2 * F_PI);
	return glm::vec2(u, v);
}

void geometry::Sphere::setWorldTransform(glm::mat4 const& transform) {
	toWorldSpaceTMat = transform;
	updateInverseTransform = true; //setter to tell object that it needs to modify it's inverse matrix
}

glm::mat4 geometry::Sphere::getWorldTransform() {
	return toWorldSpaceTMat;
}

glm::mat4 geometry::Sphere::getObjectTransform() {
	//recalculate the inverse matrix if the main transform has been updated since this was last called
	if (updateInverseTransform)
	{
		fromWorldSpaceTMat = glm::inverse(toWorldSpaceTMat);
	}
	return fromWorldSpaceTMat;
}

int geometry::Sphere::findIntersections(Ray ray, Intersection* intersections)
{
	// Transform the ray from world space to object space
	ray.position = getWorldTransform() * ray.position;
	ray.direction = getWorldTransform() * ray.direction;
	// the number of intersections is solved by the discriminant of the square root 
	// descriminant=0	1 intersection
	// descriminant>0	2 intersections
	// descriminant<0	0 intersections because square root results in an imaginary number

	auto a = glm::dot(ray.direction.xyz(), ray.direction.xyz());
	auto b = 2*glm::dot(ray.direction.xyz(), ray.position.xyz());
	auto c = glm::dot(ray.position.xyz(),ray.position.xyz()) - 1.0f; 

	auto discriminant = std::pow(b, 2) - 4 * a * c;
	if (discriminant < 0)
	{
		return 0; // there is no intersection, do not modify intersection array
	}
	else if (areSame(discriminant, 0.0f, FLT_EPSILON))
	{
		//if the discriminant is zero there is one root
		auto t = -b / (2 * a);
		auto uv = uvFromPoint(sampleRay(ray, t)); //get the uv coordinates of the intersection
		// populate the intersection array
		for (int j = 0; j < 2; j++)
		{
			intersections[j].t = t;
			intersections[j].u = uv[0];
			intersections[j].v = uv[1];
		}
		return 1; // return that there is one intersection
	}
	else
	{
		//otherwise there's two intersections
		for (int j = 0; j < 2; j++)
		{
			auto multiplier = j % 2 == 0 ? -1.0f : 1.0f; // the multiplier for the root function
			auto t = (-b + multiplier * std::sqrtf(discriminant) )/ (2 * a); // solve the 2nd order root equation
			auto uv = uvFromPoint(sampleRay(ray, t)); //get the uv coordinates of the intersection

			intersections[j].t = t;
			intersections[j].u = uv[0];
			intersections[j].v = uv[1];
		}
		return 2;
	}
	
}
