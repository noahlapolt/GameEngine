#pragma once
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "Entity.h"
#include "Texture.h"

class PlanetTerrain
{
public:
	//Pos is x, y and z point
	PlanetTerrain(glm::vec3 pos, float radius, int density, int viewDistance);
	~PlanetTerrain();

	/*
		Adds a cunk of land to the model.
		@param pos
			Location around which the chunk is made.
		@param radius
			Size of the planet.
	*/
	void updateCunk(glm::vec3 pos, float horizontalAngle);

	Entity * planetEntity;

private:
	int n_density, n_viewDistance, n_step;
	float n_radius;
	glm::vec3 n_center;

	int a = 0;

	void addTile(int index, glm::vec2 pos, glm::vec2 direction);

	//Texture Stuff
	Texture n_planetTexture;

	//Points
	std::vector<glm::vec4> n_points = { glm::vec4(1.0f, 0.0f, 1.0f, 1.0f), glm::vec4(1.0f, 0.0f, -1.0f, 1.0f), glm::vec4(-1.0f, 0.0f, 1.0f, 1.0f), glm::vec4(-1.0f, 0.0f, -1.0f, 1.0f) };

	//Model stuff
	GLuint n_vbo, n_ubo;
	std::vector<glm::vec3> n_vertices;
	std::vector<glm::vec2> n_uvs;
};

