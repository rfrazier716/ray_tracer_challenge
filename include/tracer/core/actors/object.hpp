/**
 * \class Object
 *
 *
 * \brief Base object that all tracer objects inherit from
 *
 *  has a position in the world coordinate system. To uniquely identify different objects use their pointer values 
 *
 */

#pragma once
#include "tracer/geometry/primitives.hpp"

namespace tracer
{
    namespace actor
    {
        class Object
        {
        private:
            POINT worldCoordinate = geometry::point(0, 0, 0); //!< The world coordinate position of the object

        public:
            /**
            * Returns the world coordinate of the Object
            */
            auto getWorldCoordinate() { return worldCoordinate; }

        };
    }
}