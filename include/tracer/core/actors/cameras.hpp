#pragma once

#include "tracer/core/actors/actor.hpp"

namespace tracer {
	namespace actor
	{
		class Camera : public Actor
		{
		protected:
			const float width;
		public:
			virtual geometry::Ray getRay(int xPx, int yPx, int renderWidth, int renderHeight){return geometry::Ray{};}
			virtual geometry::Ray getRandomRay(){return geometry::Ray{};}

			Camera(float camWidth=1.0f) : width(camWidth) 
			{
				//Cameras have a point source as their surface
				surfaceGeometry = std::make_unique<geometry::PointSurface>();
			}
		};

		typedef std::unique_ptr<Camera> pCamera;
		typedef std::shared_ptr<Camera> pSCamera;
		/**
		* An orthographic camera with a width, the height is set by the renderer aspect ratio
		*/
		class OrthoCamera : public Camera
		{
		public:
			geometry::Ray getRay(int xPx, int yPx, int renderWidth, int renderHeight);
			OrthoCamera(float camWidth) : Camera(camWidth) {}
		};

	}
}