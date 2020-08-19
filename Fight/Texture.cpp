#include "Texture.h"


Texture::Texture(const char* textureFile)
{
	loadImage(textureFile, n_image, n_width, n_height);
	n_file = textureFile;

	//Readys texture data
	glGenTextures(1, &n_textureID); //Generates texture buffer
	glBindTexture(GL_TEXTURE_2D, n_textureID); //Binds texture buffer
	glTexImage2D(GL_TEXTURE_2D, 0, 4, n_width, n_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &n_image[0]); //Gives texture buffer data
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //Texture settings
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //Texture settings
}


Texture::~Texture()
{
	glDeleteBuffers(1, &n_textureID);
	n_image.clear();
}