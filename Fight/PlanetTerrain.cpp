#include "PlanetTerrain.h"

PlanetTerrain::PlanetTerrain(glm::vec3 pos, float radius, int density, int viewDistance) : n_planetTexture("Data/white.png")
{
	n_density = density; //Changes how many edges the shape has
	n_viewDistance = viewDistance * density;
	n_radius = radius;
	n_center = pos;
	n_step = 1.0f / n_density;

	glm::vec3 currentPos = pos;
	int count = 0, layer = 1;
	//cented octagonal number
	int end = ((n_viewDistance) * (n_viewDistance)) + (n_viewDistance - 1) * (n_viewDistance - 1);

	while (count < end) {
		//Creates the shape
		int index = 0;
		int changeX = 1, changeY = -1;

		do {
			glm::vec3 vertices[4] = { glm::vec3(-n_step + currentPos.x, sqrt((radius * radius) - ((-n_step + currentPos.x) * (-n_step + currentPos.x)) - (( n_step + currentPos.z) * ( n_step + currentPos.z))),  n_step + currentPos.z),
									  glm::vec3( n_step + currentPos.x, sqrt((radius * radius) - (( n_step + currentPos.x) * ( n_step + currentPos.x)) - (( n_step + currentPos.z) * ( n_step + currentPos.z))),  n_step + currentPos.z),
									  glm::vec3(-n_step + currentPos.x, sqrt((radius * radius) - ((-n_step + currentPos.x) * (-n_step + currentPos.x)) - ((-n_step + currentPos.z) * (-n_step + currentPos.z))), -n_step + currentPos.z),
									  glm::vec3( n_step + currentPos.x, sqrt((radius * radius) - (( n_step + currentPos.x) * ( n_step + currentPos.x)) - ((-n_step + currentPos.z) * (-n_step + currentPos.z))), -n_step + currentPos.z)};

			glm::vec2 uvs[4] = { glm::vec2(1.0f, 0.0f),
								 glm::vec2(0.0f, 1.0f),
								 glm::vec2(0.0f, 0.0f),
								 glm::vec2(1.0f, 1.0f)};

			//First Triangle
			n_vertices.push_back(vertices[1]);
			n_vertices.push_back(vertices[2]);
			n_vertices.push_back(vertices[0]);

			n_uvs.push_back(uvs[0]);
			n_uvs.push_back(uvs[1]);
			n_uvs.push_back(uvs[2]);

			//Second Triangle
			n_vertices.push_back(vertices[1]);
			n_vertices.push_back(vertices[3]);
			n_vertices.push_back(vertices[2]);

			n_uvs.push_back(uvs[0]);
			n_uvs.push_back(uvs[3]);
			n_uvs.push_back(uvs[1]);

			//Updates all of the variables
			index++;
			currentPos += glm::vec3(2 * n_step*changeX, 0.0f, 2 * n_step*changeY);
			if (layer > 1) {
				if (index % (layer - 1) == 0) {
					if (changeX == 1 && changeY == -1) {
						changeY = 1;
					}
					else if (changeX == 1 && changeY == 1) {
						changeX = -1;
					}
					else if (changeX == -1 && changeY == 1) {
						changeY = -1;
					}
				}
			}
			count++;

		} while (count < ((layer) *(layer) + (layer - 1) * (layer - 1)));

		//Moves to bottom
		currentPos = pos - glm::vec3(2*layer*n_step, 0.0f, 0.0f);

		layer++;
	}

	/*
		Set up GL data for temporary use.
	*/
	//Readys vertex data
	glGenBuffers(1, &n_vbo); //Generates vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, n_vbo); //Binds vertex buffer
	glBufferData(GL_ARRAY_BUFFER, n_vertices.size() * sizeof(glm::vec3), &n_vertices[0], GL_STATIC_DRAW); //Gives vertex buffer data

	//Readys uv data
	glGenBuffers(1, &n_ubo); //Generates uv buffer
	glBindBuffer(GL_ARRAY_BUFFER, n_ubo); //Binds uv buffer
	glBufferData(GL_ARRAY_BUFFER, n_uvs.size() * sizeof(glm::vec2), &n_uvs[0], GL_STATIC_DRAW); //Gives uv buffer data


	planetEntity = new Entity(n_vbo, n_ubo, n_vertices.size(), n_planetTexture.getTextureID(), n_planetTexture.getTextureID(), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f), 0.0f, EntityType::NEWE, EntityMovment::STATIC);
}


PlanetTerrain::~PlanetTerrain()
{
	glDeleteBuffers(1, &n_vbo);
	glDeleteBuffers(1, &n_ubo);
}


/*
	Adds a cunk of land to the model.
	@param pos
		Location around which the chunk is made.
	@param radius
		Size of the planet.
*/
void PlanetTerrain::updateCunk(glm::vec3 pos, float horizontalAngle)
{
	
	glm::vec3 updatePos = n_center - pos;
	printf("UpdatePos: %f, %f, %f\n", updatePos.x, updatePos.y, updatePos.z);
	printf("Center: %f, %f, %f\n", n_center.x, n_center.y, n_center.z);
	printf("CurrentPos: %f, %f, %f\n", pos.x, pos.y, pos.z);

	/*
		If change in one direction is great enough add move a layer the last layer is viewDistance big on one side.

	*/

	//planetEntity->setPosition(glm::vec3(n_oldPos.x, 0.0f, n_oldPos.z));

	if (updatePos.x > 2 * n_step)
	{
		n_center.x -= 2 * n_step;
		addTile(n_vertices.size(), glm::vec2(n_center.x - (2 * (n_viewDistance - 1) * n_step) - 1, n_center.z), glm::vec2(-1.0f, 0.0f));
	}
	if (updatePos.x < 2 * -n_step) {
		n_center.x += 2 * n_step;
	}
	if (updatePos.z > 2 * n_step) {
		n_center.z -= 2 * n_step;
	}
	if (updatePos.z < 2 * -n_step) {
		n_center.z += 2 * n_step;
	}

	//Clears the old buffers.
	glDeleteBuffers(1, &n_vbo);

	//Generates the new vertex buffer.
	glGenBuffers(1, &n_vbo); //Generates vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, n_vbo); //Binds vertex buffer
	glBufferData(GL_ARRAY_BUFFER, n_vertices.size() * sizeof(glm::vec3), &n_vertices[0], GL_STATIC_DRAW); //Gives vertex buffer data

	planetEntity->setVertexID(n_vbo);
	planetEntity->setVBOSize(n_vertices.size());
}

void PlanetTerrain::addTile(int index, glm::vec2 pos, glm::vec2 direction)
{
	glm::vec3 vertices[4] = { glm::vec3(-n_step + pos.x, sqrt((n_radius * n_radius) - (((-n_step + pos.x) - n_center.x) * ((-n_step + pos.x) - n_center.x)) - ((( n_step + pos.y) - n_center.z) * (( n_step + pos.y) - n_center.z))),  n_step + pos.y),
							  glm::vec3( n_step + pos.x, sqrt((n_radius * n_radius) - ((( n_step + pos.x) - n_center.x + direction.x) * (( n_step + pos.x) - n_center.x)) - ((( n_step + pos.y) - n_center.z) * (( n_step + pos.y) - n_center.z))),  n_step + pos.y),
							  glm::vec3(-n_step + pos.x, sqrt((n_radius * n_radius) - (((-n_step + pos.x) - n_center.x) * ((-n_step + pos.x) - n_center.x)) - (((-n_step + pos.y) - n_center.z) * ((-n_step + pos.y) - n_center.z))), -n_step + pos.y),
							  glm::vec3( n_step + pos.x, sqrt((n_radius * n_radius) - ((( n_step + pos.x) - n_center.x + direction.x) * (( n_step + pos.x) - n_center.x)) - (((-n_step + pos.y) - n_center.z) * ((-n_step + pos.y) - n_center.z))), -n_step + pos.y) };

	//Insert the new ones
	//First triangle
	n_vertices.insert(n_vertices.begin() + index, vertices[1]);
	n_vertices.insert(n_vertices.begin() + index + 1, vertices[2]);
	n_vertices.insert(n_vertices.begin() + index + 2, vertices[0]);

	//Second triangle
	n_vertices.insert(n_vertices.begin() + index + 3, vertices[1]);
	n_vertices.insert(n_vertices.begin() + index + 4, vertices[3]);
	n_vertices.insert(n_vertices.begin() + index + 5, vertices[2]);
	
}