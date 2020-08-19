#pragma once
#include <vector>
#include <glm/glm.hpp>

const int SIZEMAP = 129;

class Terrain
{
public:
	Terrain();
	~Terrain();

	void generateTerrain();

	float getHeight(int x, int z) { return n_terrain[x][z]; };

	std::vector<glm::vec3> getTerrainVerts() { return n_vertices; };
	std::vector<glm::vec2> getTerrainUVs() { return n_UVs; };


private:
	int n_terrain[SIZEMAP][SIZEMAP];
	std::vector<glm::vec3> n_vertices;
	std::vector<glm::vec2> n_UVs;

	void diamondSquare(int Array[SIZEMAP][SIZEMAP], int size);
	void squareStep(int Array[SIZEMAP][SIZEMAP], int x, int z, int reach);
	void diamondStep(int Array[SIZEMAP][SIZEMAP], int x, int z, int reach);

	float random(int range);

	void triangulateTerrain(int terrain[SIZEMAP][SIZEMAP]);

};

