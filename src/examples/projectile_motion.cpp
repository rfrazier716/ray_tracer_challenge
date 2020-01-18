#include <glm/glm.hpp> //include 3D vector for position
#include <iostream>
#include <sstream>
#include <string>
#include "tracer/geometry.hpp"

class projectile
{
	public:
		int timestep = 0;
		glm::vec4 position=point(0,0,0);
		const glm::vec4 gravity = vector(0, -1, 0);
		glm::vec4 velocity=vector(0,0,0);

	void set_velocity(float x, float y, float z)
	{
		velocity = glm::vec4(x,y,z,0);
	}

	void time_tick()
	{
		//increment the timestep
		timestep += 1;
		//apply gravity to velocity
		velocity+= gravity;
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
	cannonball.set_velocity(10, 10, 0); // initialize velocity
	std::cout << "initial position of cannonball" << GlmVectorString(cannonball.position) << std::endl;
	cannonball.time_tick(); // advance the timestep
	//loop until cannonball intersects ground
	std::cout << sizeof(glm::vec4)<<std::endl;
	std::cout << sizeof(glm::vec4 *) << std::endl;
	std::cout << sizeof(cannonball) << std::endl;
	std::cout << sizeof(projectile) << std::endl;
	while (cannonball.position.y >= 0)
	{
		cannonball.time_tick();
		std::cout << "Step" << cannonball.timestep << "\t position" << GlmVectorString(cannonball.position) << std::endl;
	}
	std::cout << "Cannonball terminated after " << cannonball.timestep << " timesteps" << std::endl;
	return 0;
}