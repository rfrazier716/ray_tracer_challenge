#pragma once

#include "tracer/canvas.hpp"

namespace tracer {
	namespace actor
	{
		class Camera {
		private:
			canvasPtr imageCanvas=std::make_unique<Canvas>(new Canvas()); 
		};
	}
}