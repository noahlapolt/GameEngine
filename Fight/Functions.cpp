#include "Functions.h"

void loadImage(const char* filename, std::vector<unsigned char> &texture, unsigned &width, unsigned &height) {
	std::vector<unsigned char> png;

	//load and decode
	unsigned error = lodepng::load_file(png, filename);
	if (!error)
	{
		error = lodepng::decode(texture, width, height, png);
	}
	else
	{
		printf("Failed to load image %s.\n", filename);
	}
}

float distanceBetween(glm::vec3 pos1, glm::vec3 pos2) {
	return sqrt((pos2.x - pos1.x)*(pos2.x - pos1.x) + (pos2.y - pos1.y)*(pos2.y - pos1.y) + (pos2.z - pos1.z)*(pos2.z - pos1.z));
}