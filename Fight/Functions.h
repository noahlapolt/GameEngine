#pragma once
#include "lodepng.h"
#include <glm/glm.hpp>

//Functions
/*
	Makes an image from a file and gets it's width and height

	@param filename
		The filepath for the texture
	@param texture
		Location that the image reader files with texture data
	@param width
		The width of the texture
	@param height
		The height of the texture
*/
void loadImage(const char* filename, std::vector<unsigned char> &texture, unsigned &width, unsigned &height);
float distanceBetween(glm::vec3 pos1, glm::vec3 pos2);