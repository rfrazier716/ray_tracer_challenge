#include "tracer/matrixTransforms.hpp"

glm::mat4 translationMatrix(float x, float y, float z)
{
	return glm::mat4(
		1.0f, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		x, y, z, 1);

}

glm::mat4 translationMatrix(float translation)
{
	return glm::mat4(
		1.0f, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		translation, translation, translation, 1);

}

glm::mat4 rotationMatrix(float angle, glm::vec3 revolutionAxis)
{
	auto u = glm::normalize(revolutionAxis); //normalize the axis of revolution
	auto cosX = std::cos(angle); //calculate the cosine once
	auto sinX = std::sin(angle); //calculate the sine once
	auto u2 = u * u; // the u vector squared
	//build the matrix by column to make definition easier
	auto c0 = glm::vec4(
		cosX * u2.x *(1-cosX),
		u.x*u.y*(1-cosX)+u.z*sinX,
		u.z*u.x*(1-cosX)-u.y*sinX,
		0
		);
}

glm::mat4 scaleMatrix(float scaleX, float scaleY, float scaleZ)
{
	//returns a 4x4 scaling matrix
	return glm::mat4(
		scaleX, 0, 0, 0,
		0, scaleY, 0, 0,
		0, 0, scaleZ, 0,
		0, 0, 0, 1.0f
	);
}

glm::mat4 scaleMatrix(float scale)
{
	//returns a 4x4 scaling matrix
	return glm::mat4(
		scale, 0, 0, 0,
		0, scale, 0, 0,
		0, 0, scale, 0,
		0, 0, 0, 1.0f
	);
}

glm::vec4 translate(glm::vec4 &tuple, glm::mat4 &translationMatrix)
{
	return translationMatrix * tuple;
}

glm::vec4 rotate(glm::vec4 &tuple, glm::mat4 &rotationMatrix)
{
	return rotationMatrix * tuple;
}

glm::vec4 scale(glm::vec4& tuple, glm::mat4& scaleMatrix)
{
	return  scaleMatrix * tuple;
}