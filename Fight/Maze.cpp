#include "Maze.h"

Maze::Maze()
{
}


Maze::~Maze()
{
}

void Maze::generateMaze(int maze[SIZEMAZE][SIZEMAZE]) {
	std::vector<glm::vec2> visitedNodes;
	
	int step = 7;

	for (int r = 0; r < SIZEMAZE; r++) {
		for (int c = 0; c < SIZEMAZE; c++) {
			maze[r][c] = 1;
		}
	}

	visitedNodes.push_back(glm::vec2(1, 1));

	std::srand((unsigned int)time(NULL));

	for (int r = 1; r < SIZEMAZE; r += step) {
		for (int c = 1; c < SIZEMAZE; c += step) {
			maze[r][c] = (std::rand() % 4) + 2;
		}
	}

	while (visitedNodes.size() > 0) {
		int max = 0;
		int pos = 0;
		int direction = -1;

		//finds max
		for (int v = 0; v < visitedNodes.size(); v++) {
			int currentMax = 0;

			int top = 0;
			if ((int)visitedNodes[v].x - step >= 0) {
				top = maze[(int)visitedNodes[v].x - step][(int)visitedNodes[v].y];
			}

			int bottom = 0;
			if ((int)visitedNodes[v].x + step < SIZEMAZE) {
				bottom = maze[(int)visitedNodes[v].x + step][(int)visitedNodes[v].y];
			}

			int left = 0;
			if ((int)visitedNodes[v].y - step >= 0) {
				left = maze[(int)visitedNodes[v].x][(int)visitedNodes[v].y - step];
			}

			int right = 0;
			if ((int)visitedNodes[v].y + step < SIZEMAZE) {
				right = maze[(int)visitedNodes[v].x][(int)visitedNodes[v].y + step];
			}

			int near[4] = { top, bottom, left, right };
			for (int i = 0; i < 4; i++) {
				if (near[i] > max) {
					max = near[i];
					direction = i;
					pos = v;
				}
				if (near[i] > currentMax) {
					currentMax = near[i];
				}
			}

			if (currentMax <= 1) {
				visitedNodes.erase(visitedNodes.begin() + v);
				v = (int)visitedNodes.size();
			}
		}

		if (max > 0) {
			if (direction == 0) {
				if (maze[(int)visitedNodes[pos].x - step][(int)visitedNodes[pos].y] != 0) {
					visitedNodes.push_back(glm::vec2(visitedNodes[pos].x - step, visitedNodes[pos].y));
				}
				for (int i = 0; i <= step; i++) {
					maze[(int)visitedNodes[pos].x - i][(int)visitedNodes[pos].y] = 0;
					n_path.push_back(glm::vec2((int)visitedNodes[pos].x - i, (int)visitedNodes[pos].y));
				}
			}
			if (direction == 1) {
				if (maze[(int)visitedNodes[pos].x + step][(int)visitedNodes[pos].y] != 0) {
					visitedNodes.push_back(glm::vec2(visitedNodes[pos].x + step, visitedNodes[pos].y));
				}
				for (int i = 0; i <= step; i++) {
					maze[(int)visitedNodes[pos].x + i][(int)visitedNodes[pos].y] = 0;
					n_path.push_back(glm::vec2((int)visitedNodes[pos].x + i, (int)visitedNodes[pos].y));
				}
			}
			if (direction == 2) {
				if (maze[(int)visitedNodes[pos].x][(int)visitedNodes[pos].y - step] != 0) {
					visitedNodes.push_back(glm::vec2(visitedNodes[pos].x, visitedNodes[pos].y - step));
				}
				for (int i = 0; i <= step; i++) {
					maze[(int)visitedNodes[pos].x][(int)visitedNodes[pos].y - i] = 0;
					n_path.push_back(glm::vec2((int)visitedNodes[pos].x, (int)visitedNodes[pos].y - i));
				}
			}
			if (direction == 3) {
				if (maze[(int)visitedNodes[pos].x][(int)visitedNodes[pos].y + step] != 0) {
					visitedNodes.push_back(glm::vec2(visitedNodes[pos].x, visitedNodes[pos].y + step));
				}
				for (int i = 0; i <= step; i++) {
					maze[(int)visitedNodes[pos].x][(int)visitedNodes[pos].y + i] = 0;
					n_path.push_back(glm::vec2((int)visitedNodes[pos].x, (int)visitedNodes[pos].y + i));
				}
			}
		}
	}

	visitedNodes.clear();
	genHeightMap();
	//genTerrain();
	genMazeModel(maze);
}

void Maze::genHeightMap()
{
	std::srand((unsigned int)time(NULL));
	for (int r = 0; r < SIZEMAP; r++) {
		for (int c = 0; c < SIZEMAP; c++) {
			n_map[r][c] = -1;
		}
	}

	int random = 100;

	//Set Conners
	n_map[0][0] = ((float)(std::rand() % random) - random / 2);
	n_map[0][SIZEMAP - 1] = ((float)(std::rand() % random) - random / 2);
	n_map[SIZEMAP - 1][0] = ((float)(std::rand() % random) - random / 2);
	n_map[SIZEMAP - 1][SIZEMAP - 1] = ((float)(std::rand() % random) - random / 2);

	square(SIZEMAP - 1);

	for (int step = (SIZEMAP - 1) / 2; step >= 1; step /= 2) {
		diamond(step);
		square(step);
	}
}

void Maze::diamond(int step)
{
	for (int r = 0; r < SIZEMAP; r += step) {
		for (int c = 0; c < SIZEMAP; c += step) {
			float average = 0;
			int count = 0;
			if (n_map[r][c] == -1) {
				if ((c - step) >= 0)
				{
					average += n_map[r][c - (step)];
					count++;
				}

				if ((r + step) < SIZEMAP)
				{
					average += n_map[r + (step)][c];
					count++;
				}

				if ((c + step) < SIZEMAP)
				{
					average += n_map[r][c + (step)];
					count++;
				}

				if ((r - step) >= 0)
				{
					average += n_map[r - (step)][c];
					count++;
				}

				if (count > 0) {
					n_map[r][c] = ((average / count));// +((std::rand() % 10) - 5) / 20.0f);
				}
			}
		}
	}
}

void Maze::square(int step)
{
	for (int r = 0; r < (SIZEMAP - 1); r += step) {
		for (int c = 0; c < (SIZEMAP - 1); c += step) {
			if (n_map[(step / 2) + r][(step / 2) + c] == -1) {
				n_map[(step / 2) + r][(step / 2) + c] = (((n_map[step + r][step + c] + n_map[0 + r][0 + c] + n_map[0 + r][step + c] + n_map[step + r][0 + c]) / 4)); //+ ((std::rand() % 10) - 5) / 20.0f);
			}
		}
	}
}

void Maze::genMazeModel(int maze[SIZEMAZE][SIZEMAZE])
{
	//Creates Maze
	for (int i = 0; i < n_path.size(); i++) {
		//Up
		if (maze[(int)n_path[i].x - 1][(int)n_path[i].y] == 1) {
			//The height for the verts
			float leftHeight = n_map[((int)n_path[i].x) * 2 - 1][((int)n_path[i].y * 2 - 1)];
			float rightHeight = n_map[((int)n_path[i].x) * 2 - 1][((int)n_path[i].y * 2 + 1)];



			//First Triangle
			//Verts
			n_mazeVertices.push_back(glm::vec3((float)n_path[i].x - 0.5f, rightHeight, (float)n_path[i].y + 0.5f));
			n_mazeVertices.push_back(glm::vec3((float)n_path[i].x - 0.5f, rightHeight - 2.0f, (float)n_path[i].y + 0.5f));
			n_mazeVertices.push_back(glm::vec3((float)n_path[i].x - 0.5f, leftHeight - 2.0f, (float)n_path[i].y - 0.5f));
			//UVs
			n_mazeUVs.push_back(glm::vec2(0.0f, 0.0f));
			n_mazeUVs.push_back(glm::vec2(0.0f, 1.0f));
			n_mazeUVs.push_back(glm::vec2(1.0f, 1.0f));

			//Second Triangle
			//Verts
			n_mazeVertices.push_back(glm::vec3((float)n_path[i].x - 0.5f, leftHeight - 2.0f, (float)n_path[i].y - 0.5f));
			n_mazeVertices.push_back(glm::vec3((float)n_path[i].x - 0.5f, leftHeight, (float)n_path[i].y - 0.5f));
			n_mazeVertices.push_back(glm::vec3((float)n_path[i].x - 0.5f, rightHeight, (float)n_path[i].y + 0.5f));
			//UVs
			n_mazeUVs.push_back(glm::vec2(1.0f, 1.0f));
			n_mazeUVs.push_back(glm::vec2(1.0f, 0.0f));
			n_mazeUVs.push_back(glm::vec2(0.0f, 0.0f));
		}

		//Down
		if (maze[(int)n_path[i].x + 1][(int)n_path[i].y] == 1) {
			//The height for the verts
			float leftHeight = n_map[((int)n_path[i].x) * 2 + 1][((int)n_path[i].y * 2 - 1)];
			float rightHeight = n_map[((int)n_path[i].x) * 2 + 1][((int)n_path[i].y * 2 + 1)];

			//First Triangle
			//Verts
			n_mazeVertices.push_back(glm::vec3((float)n_path[i].x + 0.5f, leftHeight - 2.0f, (float)n_path[i].y - 0.5f));
			n_mazeVertices.push_back(glm::vec3((float)n_path[i].x + 0.5f, rightHeight - 2.0f, (float)n_path[i].y + 0.5f));
			n_mazeVertices.push_back(glm::vec3((float)n_path[i].x + 0.5f, rightHeight, (float)n_path[i].y + 0.5f));

			//UVs
			n_mazeUVs.push_back(glm::vec2(1.0f, 1.0f));
			n_mazeUVs.push_back(glm::vec2(1.0f, 0.0f));
			n_mazeUVs.push_back(glm::vec2(0.0f, 0.0f));

			//Second Triangle
			//Verts
			n_mazeVertices.push_back(glm::vec3((float)n_path[i].x + 0.5f, rightHeight, (float)n_path[i].y + 0.5f));
			n_mazeVertices.push_back(glm::vec3((float)n_path[i].x + 0.5f, leftHeight, (float)n_path[i].y - 0.5f));
			n_mazeVertices.push_back(glm::vec3((float)n_path[i].x + 0.5f, leftHeight - 2.0f, (float)n_path[i].y - 0.5f));
			//UVs
			n_mazeUVs.push_back(glm::vec2(0.0f, 0.0f));
			n_mazeUVs.push_back(glm::vec2(0.0f, 1.0f));
			n_mazeUVs.push_back(glm::vec2(1.0f, 1.0f));
		}

		//Left
		if (maze[(int)n_path[i].x][(int)n_path[i].y - 1] == 1) {
			//The height for the verts
			float topHeight = n_map[((int)n_path[i].x) * 2 - 1][((int)n_path[i].y * 2 - 1)];
			float bottomHeight = n_map[((int)n_path[i].x) * 2 + 1][((int)n_path[i].y * 2 - 1)];

			//First Triangle
			//Verts
			n_mazeVertices.push_back(glm::vec3((float)n_path[i].x - 0.5f, topHeight - 2.0f, (float)n_path[i].y - 0.5f));
			n_mazeVertices.push_back(glm::vec3((float)n_path[i].x + 0.5f, bottomHeight - 2.0f, (float)n_path[i].y - 0.5f));
			n_mazeVertices.push_back(glm::vec3((float)n_path[i].x + 0.5f, bottomHeight, (float)n_path[i].y - 0.5f));
			//UVs
			n_mazeUVs.push_back(glm::vec2(1.0f, 1.0f));
			n_mazeUVs.push_back(glm::vec2(1.0f, 0.0f));
			n_mazeUVs.push_back(glm::vec2(0.0f, 0.0f));

			//Second Triangle
			//Verts
			n_mazeVertices.push_back(glm::vec3((float)n_path[i].x + 0.5f, bottomHeight, (float)n_path[i].y - 0.5f));
			n_mazeVertices.push_back(glm::vec3((float)n_path[i].x - 0.5f, topHeight, (float)n_path[i].y - 0.5f));
			n_mazeVertices.push_back(glm::vec3((float)n_path[i].x - 0.5f, topHeight - 2.0f, (float)n_path[i].y - 0.5f));
			//UVs
			n_mazeUVs.push_back(glm::vec2(0.0f, 0.0f));
			n_mazeUVs.push_back(glm::vec2(0.0f, 1.0f));
			n_mazeUVs.push_back(glm::vec2(1.0f, 1.0f));
		}

		//Right
		if (maze[(int)n_path[i].x][(int)n_path[i].y + 1] == 1) {
			//The height for the verts
			float topHeight = n_map[((int)n_path[i].x) * 2 - 1][((int)n_path[i].y * 2 + 1)];
			float bottomHeight = n_map[((int)n_path[i].x) * 2 + 1][((int)n_path[i].y * 2 + 1)];

			//First Triangle
			//Verts
			n_mazeVertices.push_back(glm::vec3((float)n_path[i].x + 0.5f, bottomHeight, (float)n_path[i].y + 0.5f));
			n_mazeVertices.push_back(glm::vec3((float)n_path[i].x + 0.5f, bottomHeight - 2.0f, (float)n_path[i].y + 0.5f));
			n_mazeVertices.push_back(glm::vec3((float)n_path[i].x - 0.5f, topHeight - 2.0f, (float)n_path[i].y + 0.5f));
			//UVs
			n_mazeUVs.push_back(glm::vec2(1.0f, 1.0f));
			n_mazeUVs.push_back(glm::vec2(1.0f, 0.0f));
			n_mazeUVs.push_back(glm::vec2(0.0f, 0.0f));

			//Second Triangle
			//Verts
			n_mazeVertices.push_back(glm::vec3((float)n_path[i].x - 0.5f, topHeight - 2.0f, (float)n_path[i].y + 0.5f));
			n_mazeVertices.push_back(glm::vec3((float)n_path[i].x - 0.5f, topHeight, (float)n_path[i].y + 0.5f));
			n_mazeVertices.push_back(glm::vec3((float)n_path[i].x + 0.5f, bottomHeight, (float)n_path[i].y + 0.5f));
			//UVs
			n_mazeUVs.push_back(glm::vec2(0.0f, 0.0f));
			n_mazeUVs.push_back(glm::vec2(0.0f, 1.0f));
			n_mazeUVs.push_back(glm::vec2(1.0f, 1.0f));
		}

		//The height for the verts
		float topLeftHeight = n_map[((int)n_path[i].x) * 2 - 1][((int)n_path[i].y * 2 - 1)];
		float topRightHeight = n_map[((int)n_path[i].x) * 2 - 1][((int)n_path[i].y * 2 + 1)];
		float bottomLeftHeight = n_map[((int)n_path[i].x) * 2 + 1][((int)n_path[i].y * 2 - 1)];
		float bottomRightHeight = n_map[((int)n_path[i].x) * 2 + 1][((int)n_path[i].y * 2 + 1)];

		//Floor
		//First Triangle
		//Verts
		n_mazeVertices.push_back(glm::vec3((float)n_path[i].x + 0.5f, bottomRightHeight - 2.0f, (float)n_path[i].y + 0.5f));
		n_mazeVertices.push_back(glm::vec3((float)n_path[i].x + 0.5f, bottomLeftHeight - 2.0f, (float)n_path[i].y - 0.5f));
		n_mazeVertices.push_back(glm::vec3((float)n_path[i].x - 0.5f, topLeftHeight - 2.0f, (float)n_path[i].y - 0.5f));
		//UVs
		n_mazeUVs.push_back(glm::vec2(1.0f, 1.0f));
		n_mazeUVs.push_back(glm::vec2(1.0f, 0.0f));
		n_mazeUVs.push_back(glm::vec2(0.0f, 0.0f));

		//Second Triangle
		//Verts
		n_mazeVertices.push_back(glm::vec3((float)n_path[i].x - 0.5f, topLeftHeight - 2.0f, (float)n_path[i].y - 0.5f));
		n_mazeVertices.push_back(glm::vec3((float)n_path[i].x - 0.5f, topRightHeight - 2.0f, (float)n_path[i].y + 0.5f));
		n_mazeVertices.push_back(glm::vec3((float)n_path[i].x + 0.5f, bottomRightHeight - 2.0f, (float)n_path[i].y + 0.5f));
		//UVs
		n_mazeUVs.push_back(glm::vec2(0.0f, 0.0f));
		n_mazeUVs.push_back(glm::vec2(0.0f, 1.0f));
		n_mazeUVs.push_back(glm::vec2(1.0f, 1.0f));

		//Ceiling
		//First Triangle
		//Verts
		n_mazeVertices.push_back(glm::vec3((float)n_path[i].x - 0.5f, topLeftHeight, (float)n_path[i].y - 0.5f));
		n_mazeVertices.push_back(glm::vec3((float)n_path[i].x + 0.5f, bottomLeftHeight, (float)n_path[i].y - 0.5f));
		n_mazeVertices.push_back(glm::vec3((float)n_path[i].x + 0.5f, bottomRightHeight, (float)n_path[i].y + 0.5f));

		//UVs
		n_mazeUVs.push_back(glm::vec2(1.0f, 1.0f));
		n_mazeUVs.push_back(glm::vec2(1.0f, 0.0f));
		n_mazeUVs.push_back(glm::vec2(0.0f, 0.0f));

		//Second Triangle
		//Verts
		n_mazeVertices.push_back(glm::vec3((float)n_path[i].x + 0.5f, bottomRightHeight, (float)n_path[i].y + 0.5f));
		n_mazeVertices.push_back(glm::vec3((float)n_path[i].x - 0.5f, topRightHeight, (float)n_path[i].y + 0.5f));
		n_mazeVertices.push_back(glm::vec3((float)n_path[i].x - 0.5f, topLeftHeight, (float)n_path[i].y - 0.5f));
		//UVs
		n_mazeUVs.push_back(glm::vec2(0.0f, 0.0f));
		n_mazeUVs.push_back(glm::vec2(0.0f, 1.0f));
		n_mazeUVs.push_back(glm::vec2(1.0f, 1.0f));
	}
}

void Maze::genTerrain()
{
	for (int r = 0; r < (SIZEMAP - 1); r++) {
		for (int c = 0; c < (SIZEMAP - 1); c++) {
			//Floor
			//First Triangle
			//Verts
			n_mazeVertices.push_back(glm::vec3(r + 1, n_map[r + 1][c + 1], c + 1));
			n_mazeVertices.push_back(glm::vec3(r + 1, n_map[r + 1][c], c));
			n_mazeVertices.push_back(glm::vec3(r, n_map[r][c], c));
			//UVs
			n_mazeUVs.push_back(glm::vec2(1.0f, 1.0f));
			n_mazeUVs.push_back(glm::vec2(1.0f, 0.0f));
			n_mazeUVs.push_back(glm::vec2(0.0f, 0.0f));

			//Second Triangle
			//Verts
			n_mazeVertices.push_back(glm::vec3(r, n_map[r][c], c));
			n_mazeVertices.push_back(glm::vec3(r, n_map[r][c + 1], c + 1));
			n_mazeVertices.push_back(glm::vec3(r + 1, n_map[r + 1][c + 1], c + 1));
			//UVs
			n_mazeUVs.push_back(glm::vec2(0.0f, 0.0f));
			n_mazeUVs.push_back(glm::vec2(0.0f, 1.0f));
			n_mazeUVs.push_back(glm::vec2(1.0f, 1.0f));
		}
	}
}