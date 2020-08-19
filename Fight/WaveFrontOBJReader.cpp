#include "WaveFrontOBJReader.h"



WaveFrontOBJReader::WaveFrontOBJReader()
{
}


WaveFrontOBJReader::~WaveFrontOBJReader()
{
	n_vertices.clear();
	n_UVS.clear();
	n_normals.clear();
}

void WaveFrontOBJReader::loadOBJ(const char* file) {

	loadVertices(file);
	loadUVS(file);
	loadNormals(file);

	orderVUN(file);
}

void WaveFrontOBJReader::loadVertices(const char* file)
{
	std::ifstream myFile (file);
	std::string line = "";
	n_vertices.clear();
	bool canBreak = false;

	if (myFile.is_open()) {
		while (std::getline(myFile, line)) {
			if (line[0] == 'v' && line[1] == ' ') {
				canBreak = true;
				std::string x = "";
				std::string y = "";
				std::string z = "";
				int step = 0;

				for (int i = 1; i < line.length(); i++) {
					if (line[i] != ' ') {
						if (step == 1) {
							x += line[i];
						}
						if (step == 2) {
							y += line[i];
						}
						if (step == 3) {
							z += line[i];
						}
					}
					else {
						step++;
					}
				}
				n_vertices.push_back(glm::vec3(std::stof(x), std::stof(y), std::stof(z)));
			} else if(canBreak) {
				break;
			}
		}
	}
	else {
		printf("Failed to open file.");
	}

	myFile.close();
}

void WaveFrontOBJReader::loadUVS(const char* file)
{
	std::ifstream myFile(file);
	std::string line = "";
	n_UVS.clear();
	bool canBreak = false;

	if (myFile.is_open()) {
		while (std::getline(myFile, line)) {
			if (line[0] == 'v' && line[1] == 't') {
				canBreak = true;
				std::string x = "";
				std::string y = "";
				int step = 0;

				for (int i = 2; i < line.length(); i++) {
					if (line[i] != ' ') {
						if (step == 1) {
							x += line[i];
						}
						if (step == 2) {
							y += line[i];
						}
					}
					else {
						step++;
					}
				}
				n_UVS.push_back(glm::vec2(std::stof(x), std::stof(y)));
			}
			else if (canBreak) {
				break;
			}
		}
	}
	else {
		printf("Failed to open file.");
	}

	myFile.close();
}

void WaveFrontOBJReader::loadNormals(const char* file)
{
	std::ifstream myFile(file);
	std::string line = "";
	n_normals.clear();
	bool canBreak = false;

	if (myFile.is_open()) {
		while (std::getline(myFile, line)) {
			if (line[0] == 'v' && line[1] == 'n') {
				canBreak = true;
				std::string x = "";
				std::string y = "";
				std::string z = "";
				int step = 0;

				for (int i = 2; i < line.length(); i++) {
					if (line[i] != ' ') {
						if (step == 1) {
							x += line[i];
						}
						if (step == 2) {
							y += line[i];
						}
						if (step == 3) {
							z += line[i];
						}
					}
					else {
						step++;
					}
				}
				n_normals.push_back(glm::vec3(std::stof(x), std::stof(y), std::stof(z)));
			}
			else if (canBreak) {
				break;
			}
		}
	}
	else {
		printf("Failed to open file.");
	}

	myFile.close();
}

void WaveFrontOBJReader::orderVUN(const char* file)
{
	#pragma warning(suppress:4996)
	FILE * myFile = fopen(file, "r");
	std::string line = "";
	bool canBreak = false;
	char lineHeader[128];
	std::vector<glm::vec3> vertices, normals;
	std::vector<glm::vec2> uvs;

	if (file != NULL) {
		while (1) {
			#pragma warning(suppress:4996)
			int res = fscanf(myFile, "%s", lineHeader);
			if (res == EOF) {
				break;
			}
			if (strcmp(lineHeader, "f") == 0) {
				std::string vertex1, vertex2, vertex3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				#pragma warning(suppress:4996)
				fscanf(myFile, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
				vertices.push_back(n_vertices[vertexIndex[0] - 1]);
				vertices.push_back(n_vertices[vertexIndex[1] - 1]);
				vertices.push_back(n_vertices[vertexIndex[2] - 1]);
				uvs.push_back(n_UVS[uvIndex[0] - 1]);
				uvs.push_back(n_UVS[uvIndex[1] - 1]);
				uvs.push_back(n_UVS[uvIndex[2] - 1]);
				normals.push_back(n_normals[normalIndex[0] - 1]);
				normals.push_back(n_normals[normalIndex[1] - 1]);
				normals.push_back(n_normals[normalIndex[2] - 1]);
			}
		}
	}
	else {
		printf("Failed to open file.");
	}

	n_vertices = vertices;
	n_normals = normals;
	n_UVS = uvs;

	vertices.clear();
	normals.clear();
	uvs.clear();
}
