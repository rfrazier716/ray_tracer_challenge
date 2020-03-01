#include "..\..\include\tracer\geometry\transforms.hpp"
#include "..\..\include\tracer\geometry\transforms.hpp"
#include "..\..\include\tracer\geometry\transforms.hpp"
#include "..\..\include\tracer\geometry\transforms.hpp"
#include "tracer/geometry/transforms.hpp"

using namespace tracer;

	glm::mat4 geometry::crossProductMatrix(glm::vec4& u)
	{
		//returns a cross product matrix that can act as an operator on a vector
		return glm::mat4(
			0, u.z, -u.y, 0,
			-u.z, 0, u.x, 0,
			u.y, -u.x, 0, 0,
			0, 0, 0, 1
		);
	}

	glm::mat4 geometry::translationMatrix(float x, float y, float z)
	{
		return glm::mat4(
			1.0f, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			x, y, z, 1);

	}

	glm::mat4 geometry::translationMatrix(float translation)
	{
		return glm::mat4(
			1.0f, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			translation, translation, translation, 1);

	}

	glm::mat4 geometry::rotationMatrix(float angle, glm::vec4 revolutionAxis)
	{
		auto u = glm::normalize(revolutionAxis); //normalize the axis of revolution
		auto cosT = std::cos(angle); //calculate the cosine once
		auto sinT = std::sin(angle); //calculate the sine once

		//You did the proof on why this is the matrix already
		//define the cross product matrix 
		auto ux = crossProductMatrix(u);
		//the outer product matrix
		auto outer = glm::outerProduct(u, u);
		//identity matrix 
		auto eye = glm::mat4(1.0f);
		auto rotMat = cosT * eye + sinT * ux + (1 - cosT) * outer;
		rotMat[3].w = 1.0f; // have to force the w component to be 1.0f or it can go negative
		return rotMat;

	}

	glm::mat4 geometry::scaleMatrix(float scaleX, float scaleY, float scaleZ)
	{
		//returns a 4x4 scaling matrix
		return glm::mat4(
			scaleX, 0, 0, 0,
			0, scaleY, 0, 0,
			0, 0, scaleZ, 0,
			0, 0, 0, 1.0f
		);
	}

	glm::mat4 geometry::scaleMatrix(float scale)
	{
		//returns a 4x4 scaling matrix
		return glm::mat4(
			scale, 0, 0, 0,
			0, scale, 0, 0,
			0, 0, scale, 0,
			0, 0, 0, 1.0f
		);
	}

	glm::mat4 geometry::shearMatrix(float xy, float xz, float yx, float yz, float zx, float zy)
	{
		return glm::mat4(
			1, yx, zx, 0,
			xy, 1, zy, 0,
			xz, yz, 1, 0,
			0, 0, 0, 1
		);
	}
	glm::mat4 geometry::shearMatrix(float shear)
	{
		return shearMatrix(shear, shear, shear, shear, shear, shear);
	}

	glm::vec4 tracer::geometry::reflect(const VECTOR r, const VECTOR normal)
	{
		return r - 2 * glm::dot(r, normal) * normal;
	}

	glm::vec4 geometry::translate(glm::vec4& tuple, glm::mat4& translationMatrix)
	{
		return translationMatrix * tuple;
	}

	glm::vec4 geometry::rotate(glm::vec4& tuple, glm::mat4& rotationMatrix)
	{
		return rotationMatrix * tuple;
	}

	glm::vec4 geometry::scale(glm::vec4& tuple, glm::mat4& scaleMatrix)
	{
		return  scaleMatrix * tuple;
	}
/*
* These are commented out because the geometry library should be independent of the tracer core library
	void tracer::geometry::transform(actor::Light& light, glm::mat4 const& transformMatrix)
	{
		geometry::transform(*(light.geometry), transformMatrix);
	}

	void geometry::transform(actor::SolidBody& body, glm::mat4 const& transformMatrix)
	{
		geometry::transform(*(body.geometry), transformMatrix);
	}
*/
	void geometry::transform(geometry::UVSurface& surface, glm::mat4 const& transformMatrix)
	{
		surface.setWorldTransform(transformMatrix * surface.getWorldTransform());
	}
