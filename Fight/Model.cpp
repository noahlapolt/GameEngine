#include "Model.h"



Model::Model(std::vector<glm::vec3> vertices, std::vector<glm::vec2> uvs)
{

	//Stores the size of the array
	n_vboSize = vertices.size();

	/*
	Set up GL data
	*/
	//Readys vertex data
	glGenBuffers(1, &n_vbo); //Generates vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, n_vbo); //Binds vertex buffer
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW); //Gives vertex buffer data

	//Readys uv data
	glGenBuffers(1, &n_ubo); //Generates uv buffer
	glBindBuffer(GL_ARRAY_BUFFER, n_ubo); //Binds uv buffer
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW); //Gives uv buffer data

	//Clears ram data since it is now on the GPU
	vertices.clear();
	uvs.clear();
}


Model::~Model()
{
	glDeleteBuffers(1, &n_vbo);
	glDeleteBuffers(1, &n_ubo);
}
