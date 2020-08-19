#include "HeightMapReaderBW.h"

/*
	Creates a list a vertices base on height.
	Updates this
	@param image
		This is the image that will be used to make the height map.
		Pixel color effect on height lowest point to hightest point:
		(R:x, G:x, B:x, A:#)
		Where x represents the height.
*/
void HeightMapReaderBW::genMap(Texture tex) {
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
float HeightMapReaderBW::getHeight(int row, int column) {
	int start = 4 * row + (column * (n_height * 4));

	return (float)n_image[start];
}