#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "Texture.h"

class HeightMapReaderRGBA
{
public:
	/*
		Returns a set of vectors making a plane.
		@param image
			This is the image that will be used to make the height map.
			Pixel color effect on height lowest point to hightest point:
			Height is base 256 with numbers written:
			(R:#, G:#, B:#, A:#)
			Max height on the Y-axis is 4,294,967,295
			Examples:
				(R:0, G:0, B:0, A:1) Y = 1				A * 1
				(R:0, G:0, B:1, A:0) Y = 256			B * 256
				(R:0, G:1, B:0, A:0) Y = 65,536			G * 65,536
				(R:1, G:0, B:0, A:0) Y = 16,777,216		R * 16,777,216
				(R:255, G:255, B:255, A:255) Y = 4,294,967,295
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

	/*
		Transforms the number gathered from the height map to base 10.
		@param b256
			This is the number in base 256.
	*/
	unsigned long base256To10(int b256[4]);

};