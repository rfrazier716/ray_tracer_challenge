#include <glm/glm.hpp> //include 3D vector for position
#include <iostream>
#include <sstream>
#include <string>
#include <memory>

#include "tracer/geometry/primitives.hpp"
#include "tracer/canvas.hpp"

class projectile
{
	public:
		int timestep = 0;
		glm::vec4 position=point(0,0,0);
		const glm::vec4 gravity = vector(0, -1, 0);
		glm::vec4 velocity=vector(0,0,0);
		glm::vec4 windSpeed = vector(-.01, 0, 0);

	void set_velocity(float x, float y, float z)
	{
		velocity = glm::vec4(x,y,z,0);
	}

	void set_wind(float x, float y, float z)
	{
		windSpeed = vector(x,y,z);
	}

	void time_tick()
	{
		//increment the timestep
		timestep += 1;
		//apply gravity to velocity and wind 
		velocity+= gravity;
		velocity += windSpeed;
		//apply velocity to position
		position += velocity;
	}
};

std::string GlmVectorString(glm::vec4 vector)
{
	std::ostringstream ss;
	ss << "<" << vector.x << "," << vector.y << "," << vector.z << ">";
	return ss.str();

}

int main() 
{
	//make a new projectile instance
	auto cannonball = projectile();
	cannonball.set_velocity(20,20, 0); // initialize velocity

	//Make a new canvas to plot the projectiles position
	std::unique_ptr<Canvas> canvas = std::make_unique<Canvas>(1920,1080); //make a canvas 640x480 pixels

	std::cout << "initial position of cannonball" << GlmVectorString(cannonball.position) << std::endl;
	cannonball.time_tick(); // advance the timestep
	//loop until cannonball intersects ground
	while (cannonball.position.y >= 0)
	{
		std::cout << "Step" << cannonball.timestep << "\t position" << GlmVectorString(cannonball.position) << std::endl;
		canvas->writePixel((int)cannonball.position.x,(canvas->height-1) - (int)cannonball.position.y, RED); // put a red pixel where the cannonball is
		cannonball.time_tick();
	}
	std::cout << "Cannonball terminated after " << cannonball.timestep << " timesteps" << std::endl;
	std::cout << "writing image to disk" << std::endl;
	canvas->generateImage(ExportFormat::bmp); // write the image to disk
	return 0;
}