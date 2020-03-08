#include "tracer/core/actors/actor.hpp"

using namespace tracer;

unsigned long int actor::Actor::idCounter = 0; //initializes the counter for actor objects

//transform is defined here for actors to avoid cross inclusion with geometry library
void tracer::geometry::transform(actor::Actor& actor, glm::mat4 const& transformMatrix)
{
	actor.surfaceGeometry->setWorldTransform(transformMatrix * actor.surfaceGeometry->getWorldTransform());
}
