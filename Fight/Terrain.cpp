#include "Terrain.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h> 

Terrain::Terrain()
{
}

Terrain::~Terrain()
{
}

void Terrain::generateTerrain() {
	for (int x = 0; x < SIZEMAP; x++) {
		for (int y = 0; y < SIZEMAP; y++) {
			n_terrain[x][y] = 0.0f;
		}
	}

	std::srand(time(NULL));

	n_terrain[0][0] = (float)((std::rand() % 100) - 50);
	n_terrain[0][SIZEMAP - 1] = (float)((std::rand() % 100) - 50);
	n_terrain[SIZEMAP - 1][0] = (float)((std::rand() % 100) - 50);
	n_terrain[SIZEMAP - 1][SIZEMAP - 1] = (float)((std::rand() % 100) - 50);
	
	diamondSquare(n_terrain, 1025);

	triangulateTerrain(n_terrain);
}

void Terrain::diamondSquare(int Array[SIZEMAP][SIZEMAP], int size)
{
	int half = size / 2;
	if (half < 1)
		return;
	//square steps
	for (int z = half; z < SIZEMAP; z += size)
		for (int x = half; x < SIZEMAP; x += size)
			squareStep(Array, x % SIZEMAP, z % SIZEMAP, half);
	// diamond steps
	int col = 0;
	for (int x = 0; x < SIZEMAP; x += half)
	{
		col++;
		//If this is an odd column.
		if (col % 2 == 1)
			for (int z = half; z < SIZEMAP; z += size)
				diamondStep(Array, x % SIZEMAP, z % SIZEMAP, half);
		else
			for (int z = 0; z < SIZEMAP; z += size)
				diamondStep(Array, x % SIZEMAP, z % SIZEMAP, half);
	}
	diamondSquare(Array, size / 2);
}

void Terrain::squareStep(int Array[SIZEMAP][SIZEMAP], int x, int z, int reach)
{
	int count = 0;
	float avg = 0.0f;
	if (x - reach >= 0 && z - reach >= 0)
	{
		avg += Array[x - reach][z - reach];
		count++;
	}
	if (x - reach >= 0 && z + reach < SIZEMAP)
	{
		avg += Array[x - reach][z + reach];
		count++;
	}
	if (x + reach < SIZEMAP && z - reach >= 0)
	{
		avg += Array[x + reach][z - reach];
		count++;
	}
	if (x + reach < SIZEMAP && z + reach < SIZEMAP)
	{
		avg += Array[x + reach][z + reach];
		count++;
	}
	avg += random(reach);
	avg /= count;
	Array[x][z] = round(avg);
}

void Terrain::diamondStep(int Array[SIZEMAP][SIZEMAP], int x, int z, int reach)
{
	int count = 0;
	float avg = 0.0f;
	if (x - reach >= 0)
	{
		avg += Array[x - reach][z];
		count++;
	}
	if (x + reach < SIZEMAP)
	{
		avg += Array[x + reach][z];
		count++;
	}
	if (z - reach >= 0)
	{
		avg += Array[x][z - reach];
		count++;
	}
	if (z + reach < SIZEMAP)
	{
		avg += Array[x][z + reach];
		count++;
	}
	avg += random(reach);
	avg /= count;
	Array[x][z] = (int)avg;
}

float Terrain::random(int range)
{
	return (rand() % (range * 2)) - range;
}

void Terrain::triangulateTerrain(int terrain[SIZEMAP][SIZEMAP]) {
	for (int x = 1; x < SIZEMAP; x++) {
		for (int z = 1; z < SIZEMAP; z++) {
			n_vertices.push_back(glm::vec3(x - 1, terrain[x - 1][z - 1], z - 1));
			n_vertices.push_back(glm::vec3(x - 1, terrain[x - 1][z], z));
			n_vertices.push_back(glm::vec3(x, terrain[x][z], z));

			n_vertices.push_back(glm::vec3(x, terrain[x][z], z));
			n_vertices.push_back(glm::vec3(x, terrain[x][z - 1], z - 1));
			n_vertices.push_back(glm::vec3(x - 1, terrain[x - 1][z - 1], z - 1));

			//Triangle UVS
			n_UVs.push_back(glm::vec2(x, z));
			n_UVs.push_back(glm::vec2(x, z - 1));
			n_UVs.push_back(glm::vec2(x - 1, z - 1));

			n_UVs.push_back(glm::vec2(x - 1, z - 1));
			n_UVs.push_back(glm::vec2(x - 1, z));
			n_UVs.push_back(glm::vec2(x, z));
		}
	}
}