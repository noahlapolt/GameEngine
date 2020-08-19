#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "Texture.h"

class HeightMapReaderBW
{
public:
	/*
		Returns a set of vectors making a plane.
		@param image
			This is the image that will be used to make the height map.
			Pixel color effect on height lowest point to hightest point:
			Height is base 256 with numbers written:
			(R:x, G:x, B:x, A:#)
			Where x represents the height.
	*/
	void genMap(Texture tex);

	/*
		Get vertices of the object.
	*/
	std::vector<glm::vec3> getVertices()
	{
		return n_vertices;
	};

	/*
		Get the UVs of the object.
	*/
	std::vector<glm::vec2> getUV() {
		return n_UVs;
	};

private:
	//Private variables.
	unsigned int n_height;					//The height of the image.
	std::vector<unsigned char> n_image;		//The pixels of images.
	std::vector<glm::vec3> n_vertices;		//The object
	std::vector<glm::vec2> n_UVs;			//UVs

	/*
		Gets the height based on row and column.
		@param row
			This is the row location.
		@param column
			This is the column location.
	*/
	float getHeight(int row, int column);
};