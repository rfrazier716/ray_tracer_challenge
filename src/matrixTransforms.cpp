#include "tracer/matrixTransforms.hpp"

glm::mat4 crossProductMatrix(glm::vec4& u)
{
	//returns a cross product matrix that can act as an operator on a vector
	return glm::mat4(
		0, u.z, -u.y, 0,
		-u.z, 0, u.x, 0,
		u.y, -u.x, 0, 0,
		0, 0, 0, 1
	);
}

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

glm::mat4 rotationMatrix(float angle, glm::vec4 revolutionAxis)
{
	auto u = glm::normalize(revolutionAxis); //normalize the axis of revolution
	auto cosT = std::cos(angle); //calculate the cosine once
	auto sinT = std::sin(angle); //calculate the sine once

	//You did the proof on why this is the matrix already
	//define the cross product matrix 
	auto ux = crossProductMatrix(u);
	//the outer product matrix
	auto outer=glm::outerProduct(u, u);
	//identity matrix 
	auto eye = glm::mat4(1.0f);
	return cosT * eye + sinT * ux + (1 - cosT) * outer;

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