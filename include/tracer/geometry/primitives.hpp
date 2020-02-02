#pragma once

#include "glm/vec4.hpp"

#define X_AXIS vector(1,0,0)
#define Y_AXIS vector(0,1,0)
#define Z_AXIS vector(0,0,1)

glm::vec4 point(float x, float y, float z);
glm::vec4 vector(float x, float y, float z);

