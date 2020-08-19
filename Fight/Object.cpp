#include "Object.h"

unsigned int Object::id = 0;

Object::Object(glm::vec3 position, glm::vec3 forceDirection, float mass, float magnitude)
{
	n_id = id;
	n_position = position;
	n_forceDirection = forceDirection;
	n_mass = mass;
	n_magnitude = magnitude;

	id++;
}

Object::~Object()
{
}

void Object::update()
{
	n_position += (n_forceDirection * n_magnitude);
}