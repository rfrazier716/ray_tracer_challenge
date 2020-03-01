#include "tracer/geometry/surfaces/uvsurface.hpp"
using namespace tracer;


POINT geometry::SphericalSurface::sample(float u, float v){
	// required trig definitions calculated once for speed
	float sinU = std::sin(F_PI * u);
	float cosU = std::cos(F_PI * u);
	float sinV = std::sin(2*F_PI * v);
	float cosV = std::cos(2*F_PI * v);

	float x = sinU * cosV;
	float y = sinU * sinV;
	float z = cosU;
	//need to translate from object coordinates back into world coordinates before returning
	return getWorldTransform()*point(x, y, z);
}

VECTOR geometry::SphericalSurface::normal(float u, float v){
	// need to account for special cases when u=0 and u =1
	VECTOR du;
	VECTOR dv;
	if (u == 1.0f)
	{
		//if u=1.0f must manually set the vectors because dv is the zero vector
		du = geometry::vector(1, 0, 0);
		dv = geometry::vector(0, -1, 0);
	}
	else if (u == 0.0f)
	{
		du = geometry::vector(-1, 0, 0);
		dv = geometry::vector(0, -1, 0);
	}
	else 
	{
		auto sinU = std::sin(F_PI * u);
		auto cosU = std::cos(F_PI * u);
		auto sinV = std::sin(2 * F_PI * v);
		auto cosV = std::cos(2 * F_PI * v);
		du = geometry::vector(cosU * cosV, cosU * sinV, -sinU);
		dv = geometry::vector(-sinU * sinV, sinU * cosV, 0);
	}
	//to get the world in normal space need to transform du and dv into world space and take dVxdU
	du = getWorldTransform() * du;
	dv = getWorldTransform() * dv;
	auto norm = glm::vec4(glm::cross(du.xyz(), dv.xyz()),0); //the norm is also a vector
	norm = glm::normalize(norm); //set the magnitude of the norm to 1.0f
	return norm;
	// TODO: The book describes the normal transform by taking the transpose of the world matrix but doesn't explain why, 
	// This method has been derived and works, but uses more operations

}

VECTOR geometry::SphericalSurface::tangent(float u, float v){
	return vector(1,1,1); // this function needs to be filled in 
}

glm::vec2 geometry::SphericalSurface::uvFromPoint(float x, float y, float z)
{
	auto point = geometry::point(x, y, z); //put the floats into a point
	return uvFromPoint(point); // call the other UV from point function
}

glm::vec2 geometry::SphericalSurface::uvFromPoint(glm::vec4 point)
{
	//have to subtract 1.0f from the point magnitude because the w component of a point is 1.0
	//assert the point is on the unit sphere
	auto pointMagnitude = glm::dot(point, point) - 1.0f;
	assert(areSame(glm::dot(point,point)-1.0f, 1.0f, FLT_EPSILON) || !(std::cerr << point.x <<","<< point.y << "," << point.z << "," << point.w << "is not on the unit sphere"));
	auto theta = std::acos(point.z); 
	auto phi = std::atan2(point.y, point.x);
	auto u = theta / F_PI;
	auto v = phi / (2 * F_PI);
	return glm::vec2(u, v);
}

int geometry::SphericalSurface::findIntersections(Ray ray, Intersection* intersections)
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
