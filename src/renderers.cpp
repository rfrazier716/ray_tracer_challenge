#include "tracer/core/renderers.hpp"

//Parent Class Definitions for Render Object

using namespace tracer;


void tracer::Renderer::addBody(actor::pSSolidBody bodyPtr)
{
	renderObjects.push_back(bodyPtr);
}

void tracer::Renderer::addLight(actor::pSLight lightPtr)
{
	lights.push_back(lightPtr);
}

tracer::Renderer::Renderer(int hRes, int vRes)
{
	//create a new canvas on the heap
	canvas = std::make_unique<tracer::Canvas>(hRes, vRes);
}
