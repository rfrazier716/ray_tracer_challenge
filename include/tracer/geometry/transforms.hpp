#include "glm/mat4x4.hpp"
#include "glm/vec4.hpp"
#include <math.h>  //for trig functions
namespace tracer
{
	namespace geometry
	{
		glm::mat4 crossProductMatrix(glm::vec4& u);

		glm::mat4 translationMatrix(float x, float y, float z);
		glm::mat4 translationMatrix(float translation);

		glm::mat4 rotationMatrix(float rotation, glm::vec4 axis);

		glm::mat4 scaleMatrix(float scaleX, float scaleY, float scaleZ);
		glm::mat4 scaleMatrix(float scale);

		glm::mat4 shearMatrix(float xy, float xz, float yx, float yz, float zx, float zy);
		glm::mat4 shearMatrix(float shear);


		glm::vec4 translate(glm::vec4& tuple, glm::mat4& translationMatrix);
		glm::vec4 rotate(glm::vec4& tuple, glm::mat4& rotationMatrix);
		glm::vec4 scale(glm::vec4& tuple, glm::mat4& scaleMatrix);
	}
}