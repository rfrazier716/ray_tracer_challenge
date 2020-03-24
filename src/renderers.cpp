#include "tracer/core/renderers.hpp"



using namespace tracer;

void projectLightRay(LightRay& ray, std::vector< actor::pSActor >& actors)
{
	//project a light ray to check intersections with a vector of actors
	//find the nearest intersection and return it 
}

//Parent Class Definitions for Render Object
void tracer::Renderer::addBody(actor::pSSolidBody bodyPtr)
{
	renderObjects.push_back(bodyPtr);
}

void tracer::Renderer::addLight(actor::pSLight lightPtr)
{
	lights.push_back(lightPtr);
}


//Binary Renderer
renderStatus tracer::BinaryRenderer::render()
{
	//for the binary camera you have one ray per pixel
	for (int xPx = 0; xPx < renderHRes; xPx++)
	{
		for (int yPx = 0; yPx < renderHRes; yPx++)
		{
			//Create a render
		}
	}
}