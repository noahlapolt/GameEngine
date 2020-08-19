#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

class Model
{
public:
	Model(std::vector<glm::vec3> vertices, std::vector<glm::vec2> uvs);
	~Model();

	GLuint getVertexBuffer() { return n_vbo; };
	GLuint getUVBuffer() { return n_ubo; };
	size_t getVBOSize() { return n_vboSize; };

private:
	GLuint n_vbo, n_ubo;
	size_t n_vboSize;
};

