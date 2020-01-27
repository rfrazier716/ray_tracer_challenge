#include "tracer/matrixTransforms.hpp"

glm::mat4 translationMatrix(float x, float y, float z)
{
	return glm::mat4(
		1.0f, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		x, y, z, 1);

}

glm::mat4 rotationMatrix(float yaw, float pitch, float roll)
{
	return glm::mat4(1.0f);
}

glm::vec4 translate(glm::vec4 &tuple, glm::mat4 &translationMatrix)
{
	return translationMatrix * tuple;
}

glm::vec4 rotate(glm::vec4 &tuple, glm::mat4 &rotationMatrix)
{
	return rotationMatrix * tuple;
}