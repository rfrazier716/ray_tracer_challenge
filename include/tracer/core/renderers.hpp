#pragma once

#include "tracer/canvas.hpp"
#include "tracer/core/actors/lights.hpp"
#include "tracer/core/actors/solidbody.hpp"
#include "tracer/core/actors/cameras.hpp"

namespace tracer {
	class Renderer {
	protected:
		pCanvas canvas;
		std::vector<actor::pSLight> lights;
		std::vector < actor::pSSolidBody > renderObjects;
		actor::pSCamera camera;
	public:
		virtual int render() {return 0;} //!<This is the render function that does the meat of the work
		void addBody(actor::pSSolidBody bodyPtr); //!<inserts a body into the renderObjects vector
		void addLight(actor::pSLight lightPtr); //!<adds a light to the lighting vector
		void setCamera(actor::pSCamera cameraPtr) { camera = cameraPtr; } //!< sets the camera
		
		Renderer(int hRes, int vRes);
	};
	/**
	* A binary renderer projects rays from the camera towards the scene, if that ray intersects an object the pixel is set to 1
	*
	*/
	class BinaryRenderer {

	};
}
