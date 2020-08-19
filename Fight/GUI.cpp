#include "GUI.h"

GUI::GUI(GLuint textureID, glm::vec2 position, glm::vec2 scale, float rotation)
{
	n_position = position;
	n_rotation = rotation;
	n_scale = scale;
	n_textureID = textureID;

	GLfloat g_vertex_buffer_data[] = {
		1.0f, -1.0f,
		1.0f,  1.0f,
		-1.0f, 1.0f,

		-1.0f, 1.0f,
		-1.0f, -1.0f,
		1.0f, -1.0f
	};
	GLfloat g_uv_buffer_data[] = {
		1.0f, 1.0f,
		1.0f,  0.0f,
		0.0f, 0.0f,

		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f
	};

	initShaders();

	//Creates vertex array object
	glGenVertexArrays(1, &vao);

	//Generats the vbo if it has not been yet
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	//Set up uvs
	glGenBuffers(1, &uv);
	glBindBuffer(GL_ARRAY_BUFFER, uv);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

	n_hoverLocation = n_shaders.getUniformLocation("hover");
	n_textureLocation = n_shaders.getUniformLocation("myTextureSampler");
	n_positionLocation = n_shaders.getUniformLocation("pos");
	n_rotationLocation = n_shaders.getUniformLocation("rot");
	n_scaleLocation = n_shaders.getUniformLocation("scale");
}


GUI::~GUI()
{
	glDeleteBuffers(1, &n_textureID);
}

void GUI::initShaders() {
	//Loads the shaders
	n_shaders.compileShaders("Shaders/guiVertexShader.vert", "Shaders/guiFragmentShader.frag");
	//Links all the shaders
	n_shaders.linkShaders();
	//Adds an attributes
	n_shaders.addAttribute("vertexPosition");
	n_shaders.addAttribute("vertexUV");
}

void GUI::draw() {
	n_shaders.use();

	//Update / Change the uniform variables
	glUniform4f(n_hoverLocation, getHover().x, getHover().y, getHover().z, getHover().w);
	glUniform2f(n_positionLocation, (2 * n_position.x - 1280.0f) / 1280.0f, (-2 * n_position.y + 720.0f) / 720.0f);
	glUniform2f(n_scaleLocation, n_scale.x / 1280.0f, n_scale.y / 720.0f);
	glUniform1f(n_rotationLocation, glm::radians(n_rotation));
	glUniform1i(n_textureLocation, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, n_textureID);

	glBindVertexArray(vao);

	//Enables the first vertex and sets it up
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uv);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//Draws the triangles
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Disables the first vertex
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	//Unbinds the object from the first buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	n_shaders.unuse();
}