#pragma once
#include <GL/glew.h>

#include "Functions.h"

class Texture
{
public:
	Texture(const char* textureFile);
	~Texture();

	GLuint getTextureID() { return n_textureID; };
	std::vector<unsigned char> getImage() { return n_image; };
	unsigned int getWidth() { return n_width; };
	unsigned int getHeight() { return n_height; };

private:
	//Private Variables
	std::vector<unsigned char> n_image;
	unsigned int n_width, n_height;
	const char* n_file;
	GLuint n_textureID;

};

