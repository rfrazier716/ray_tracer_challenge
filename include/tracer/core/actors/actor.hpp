#pragma once
#include "Tracer/geometry/geometry.hpp"

namespace tracer {
	namespace actor {
		class Actor {
		private:
			static unsigned long int idCounter;
			bool rendered = true;
		public:
			const unsigned long int id; //!< the unique id of the actor, gets incremented on generation
			geometry::pUVSurface surfaceGeometry; //a pointer to the object geometry;

			Actor() : id(idCounter)
			{
				idCounter++;
			}
			void setRendered(bool isRendered) { rendered = isRendered; } //!< Sets whether or not the actor is rendered
		};
		typedef std::shared_ptr<Actor> pSActor;
	}

	

	namespace geometry
	{
		void transform(actor::Actor& actor, glm::mat4 const& transformMatrix); //!< Transform function for an actor object
		void move(actor::Actor& actor, float dx=0.0f, float dy=0.0f, float dz=0.0f);
		void moveAbs(actor::Actor& actor, float x = 0.0f, float y = 0.0f, float z = 0.0f);
		//Defined here to separate geometry library dependence on actor library
	}
}