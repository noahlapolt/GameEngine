#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class Object
{
public:
	//Constructer Deconstructer
	Object(glm::vec3 position, glm::vec3 direction, float mass, float magnitude);
	~Object();

	static unsigned int id;

	//Getters
	glm::vec3 getForceDirection()
	{
		return n_forceDirection;
	};
	glm::vec3 getPosition()
	{
		return n_position;
	}
	float getMass()
	{
		return n_mass;
	};
	float getMagnitude() 
	{
		return n_magnitude;
	};
	float getVelocity()
	{
		return n_velocity;
	};
	unsigned int getID() { return n_id; };

	//Setters
	void setPosition(glm::vec3 position) 
	{
		n_position = position;
	};
	void setForceDirection(glm::vec3 forceDirection)
	{
		n_forceDirection = forceDirection;
	};
	void setMagnitude(float magnitude) 
	{
		n_magnitude = magnitude;
	};
	void setVelocity(float velocity)
	{
		n_velocity = velocity;
	}
	void setMass(float mass) 
	{ 
		n_mass = mass;
	};

	void update();

private:
	//Private Variables
	glm::vec3 n_position, n_forceDirection;
	float n_mass, n_magnitude, n_velocity = 0;
	unsigned int n_id;
};