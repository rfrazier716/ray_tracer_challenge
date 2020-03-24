#include "tracer/core/actors/actor.hpp"

using namespace tracer;

unsigned long int actor::Actor::idCounter = 0; //initializes the counter for actor objects

//transform is defined here for actors to avoid cross inclusion with geometry library
void tracer::geometry::transform(actor::Actor& actor, glm::mat4 const& transformMatrix)
{
	actor.surfaceGeometry->setWorldTransform(transformMatrix * actor.surfaceGeometry->getWorldTransform());
}

void tracer::geometry::move(actor::Actor& actor, float dx, float dy, float dz)
{
	actor.surfaceGeometry->setWorldTransform(geometry::translationMatrix(dx, dy, dz) * actor.surfaceGeometry->getWorldTransform());
}

void tracer::geometry::moveAbs(actor::Actor& actor, float x, float y, float z)
{
	auto translation=geometry::point(x,y,z)-actor.surfaceGeometry->getWorldOrigin();
	actor.surfaceGeometry->setWorldTransform(geometry::translationMatrix(translation.x, translation.y, translation.z) * actor.surfaceGeometry->getWorldTransform());
}

