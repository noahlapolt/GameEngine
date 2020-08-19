#include "HeightMapReaderRGBA.h"

/*
	Creates a list a vertices base on height.
	Updates this
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
void HeightMapReaderRGBA::genMap(Texture tex) {
	n_image = tex.getImage();
	n_height = tex.getHeight();

	int row = 0, column = 0;

	for (int pixel = 0; pixel < n_image.size(); pixel += 4) {
		//First triangle
		n_vertices.push_back(glm::vec3(row, getHeight(row, column), column));
		n_vertices.push_back(glm::vec3(row, getHeight(row, column + 1), column + 1.0f));
		n_vertices.push_back(glm::vec3(row + 1.0f, getHeight(row + 1, column + 1), column + 1.0f));

		//Second triangle
		n_vertices.push_back(glm::vec3(row + 1.0f, getHeight(row + 1, column + 1), column + 1.0f));
		n_vertices.push_back(glm::vec3(row + 1.0f, getHeight(row + 1, column), column));
		n_vertices.push_back(glm::vec3(row, getHeight(row, column), column));
		

		//Triangle UVS
		n_UVs.push_back(glm::vec2(row + 1, column + 1));
		n_UVs.push_back(glm::vec2(row + 1, column));
		n_UVs.push_back(glm::vec2(row, column));

		n_UVs.push_back(glm::vec2(row, column));
		n_UVs.push_back(glm::vec2(row, column + 1));
		n_UVs.push_back(glm::vec2(row + 1, column + 1));
		

		//Updates row and/or column
		row++;
		if (row == (n_height - 1)) {
			column++;
		}

		row %= (n_height - 1);
		column %= (tex.getWidth() - 1);
	}
}

/*
	Gets the height based on row and column.
	@param row
		This is the row location.
	@param column
		This is the column location.
*/
float HeightMapReaderRGBA::getHeight(int row, int column) {
	int b256[4];
	int start = 4 * row + (column * (n_height * 4));
	
	b256[0] = n_image[start];
	b256[1] = n_image[start + 1];
	b256[2] = n_image[start + 2];
	b256[3] = n_image[start + 3];

	return base256To10(b256) * 0.00000465661f;
}

/*
	Transforms the number gathered from the height map to base 10.
	@param b256
		This is the number in base 256.
*/
unsigned long HeightMapReaderRGBA::base256To10(int b256[4]) {
	unsigned long base10 = 0;
	base10 += b256[0] * 16777216;
	base10 += b256[1] * 65536;
	base10 += b256[2] * 256;
	base10 += b256[3];

	return base10;
}