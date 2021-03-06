#pragma once

#include "tracer/core/actors/actor.hpp"

namespace tracer {
	namespace actor
	{
		class Camera : public Actor
		{
		protected:
			float aspectRatio=1.0; //!< Aspect Ratio is the ratio of height to width 
		public:
			void setAspectRatio(float ratio) { aspectRatio = ratio; }
			float getAspectRatio() { return aspectRatio; }

			virtual geometry::Ray getRay(float xPct,float yPct){return geometry::Ray{};}
			virtual geometry::Ray getRandomRay(){return geometry::Ray{};}


			Camera()
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
		private:
			float orthoWidth;
		public:
			geometry::Ray getRay(float xPct, float yPct);
			OrthoCamera(float camWidth)
			{
				orthoWidth = camWidth;
			}
		};

	}
}