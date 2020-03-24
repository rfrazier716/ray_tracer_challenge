#pragma once

#include "tracer/canvas.hpp"
#include "tracer/core/lightray.hpp"
#include "tracer/core/actors/lights.hpp"
#include "tracer/core/actors/solidbody.hpp"
#include "tracer/core/actors/cameras.hpp"

namespace tracer {

	enum class renderStatus {
		RENDER_SUCCESS,
		RENDER_FAIL
	};

	class Renderer {
	protected:
		const int renderHRes;
		const int renderVRes;
		pCanvas canvas;
		std::vector<actor::pSLight> lights;
		std::vector < actor::pSSolidBody > renderObjects;
		std::vector <LightRay> rays;
		actor::pSCamera camera;

		void validateRenderer(); //!< Checks that the renderer has the required components and the vectors of lights and objects are populated
	public:
		virtual renderStatus render() { return renderStatus::RENDER_FAIL; } //!<This is the render function that does the meat of the work
		void addBody(actor::pSSolidBody bodyPtr); //!<inserts a body into the renderObjects vector
		void addLight(actor::pSLight lightPtr); //!<adds a light to the lighting vector
		void setCamera(actor::pSCamera cameraPtr) { camera = cameraPtr; } //!< sets the camera
		
		Renderer(int hRes, int vRes) : renderHRes(hRes), renderVRes(vRes) {}
	};
	/**
	* A binary renderer projects rays from the camera towards the scene, if that ray intersects an object the pixel is set to 1
	*
	*/
	class BinaryRenderer : public Renderer
	{
	private:
	public:
		BinaryRenderer(int hRes, int vRes) : Renderer(hRes, vRes) {}
	};
}
