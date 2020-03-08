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
	}
	namespace geometry
	{
		void transform(actor::Actor& actor, glm::mat4 const& transformMatrix); //!< Transform function for a light object
		//Defined here to separate geometry library dependence on actor library
	}
}