#include "glm/mat4x4.hpp"
#include "glm/vec4.hpp"

glm::mat4 translationMatrix(float x, float y, float z);
glm::mat4 rotationMatrix(float yaw, float pitch, float roll);

glm::vec4 translate(glm::vec4 &tuple, glm::mat4 &translationMatrix);
glm::vec4 rotate(glm::vec4 &tuple, glm::mat4 &rotationMatrix);