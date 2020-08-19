#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

class WaveFrontOBJReader
{
public:
	WaveFrontOBJReader();
	~WaveFrontOBJReader();

	std::vector<glm::vec3> getVertices() { return n_vertices; };
	std::vector<glm::vec3> getNormals() { return n_normals; };
	std::vector<glm::vec2> getUVs() { return n_UVS; };

	void loadOBJ(const char* file);

private:
	void loadVertices(const char* file);
	void loadUVS(const char* file);
	void loadNormals(const char* file);
	void orderVUN(const char* file);

	std::vector<glm::vec3> n_vertices = { glm::vec3(0.0f) };
	std::vector<glm::vec2> n_UVS = { glm::vec2(0.0f) };
	std::vector<glm::vec3> n_normals = { glm::vec3(0.0f) };
};

