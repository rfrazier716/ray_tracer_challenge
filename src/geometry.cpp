#include "tracer/geometry.hpp"




extern glm::vec4 point(float x, float y, float z);
extern glm::vec4 vector(float x, float y, float z);

float toRad(float degree) { return (degree * M_PI / 180.0); }
//converts degree to radians

float toDeg(float rad) { return (rad * 180.0 / M_PI); }
//converts radians to degrees
