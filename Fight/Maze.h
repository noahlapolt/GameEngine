#pragma once

#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <vector>
#include <glm/glm.hpp>

class Maze
{
public:
	Maze();
	~Maze();

	//getters
	float getMazeHeight(int x, int z)
	{
		return n_map[x][z];
	}

	const static int SIZEMAZE = 129;
	const static int SIZEMAP = (SIZEMAZE - 1) * 2 + 1;
	void generateMaze(int maze[SIZEMAZE][SIZEMAZE]);

	std::vector<glm::vec3> getVertices()
	{
		return n_mazeVertices;
	}
	std::vector<glm::vec2> getUVS()
	{
		return n_mazeUVs;
	}

private:
	float n_map[SIZEMAP][SIZEMAP];

	void genHeightMap();
	void diamond(int step);
	void square(int step);
	void genMazeModel(int maze[SIZEMAZE][SIZEMAZE]);
	void genTerrain();
	
	std::vector<glm::vec2> n_path;
	std::vector<glm::vec3> n_mazeVertices;
	std::vector<glm::vec2> n_mazeUVs;

};

