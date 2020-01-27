#include "glm/mat4x4.hpp"
#include "glm/vec4.hpp"
#include <math.h>  //for trig functions

glm::mat4 translationMatrix(float x, float y, float z);
glm::mat4 translationMatrix(float translation);

glm::mat4 rotationMatrix(float yaw, float pitch, float roll);
glm::mat4 rotationMatrix(float rotation);

glm::mat4 scaleMatrix(float scaleX, float scaleY, float scaleZ);
glm::mat4 scaleMatrix(float scale);


glm::vec4 translate(glm::vec4 &tuple, glm::mat4 &translationMatrix);
glm::vec4 rotate(glm::vec4 &tuple, glm::mat4 &rotationMatrix);
glm::vec4 scale(glm::vec4 &tuple, glm::mat4 &scaleMatrix);