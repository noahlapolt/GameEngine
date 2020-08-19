#pragma once
#include <sdl/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>


#include "Functions.h"
#include "Window.h"
#include "GLSLContext.h"
#include "Texture.h"

class GUI
{
public:
	GUI(GLuint textureID, glm::vec2 position, glm::vec2 scale, float rotation);
	~GUI();

	void draw();

	//Getters
	glm::vec4 getHover() { return n_hover; };
	glm::vec2 getPosition() { return n_position; };
	glm::vec2 getScale() { return n_scale; };
	float getRotation() { return n_rotation; };

	//Setters
	void setHover(glm::vec4 newHover) { n_hover = newHover; };
	void setPosition(glm::vec2 position) { n_position = position; };
	void setScale(glm::vec2 scale) { n_scale = scale; };
	void setRotation(float rotation) { n_rotation = rotation; };

private:
	void initShaders();

	glm::vec2 n_position, n_scale;
	float n_rotation;

	GLuint n_hoverLocation, n_textureLocation, n_positionLocation, n_rotationLocation, n_scaleLocation;
	GLSLContext n_shaders;
	GLuint uv, n_textureID, vbo, vao;

	glm::vec4 n_hover = glm::vec4(0.0f); //The hover overlay
};
