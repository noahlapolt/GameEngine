#pragma once
#include <string>

#include <GL\glew.h>

class GLSLContext
{
public:
	//Creates shaders
	void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

	//Adds attributes 
	void addAttribute(const std::string& atribName);

	//Attaches shader to the program
	void linkShaders();

	//uses the shaders
	void use();
	//ununses the shader
	void unuse();

	//Finds the loaction of a uniform variable
	GLint getUniformLocation(const std::string& uniformName);

private:
	//Compiles the shader
	void compileShader(const std::string& filePath, GLuint id);

	//Variables
	int n_numAtrtibs = 0; //Number of attributes
	GLuint n_programID = 0; //The program id
	GLuint n_vertexShaderID = 0; //The vertex shader id
	GLuint n_fragmentShaderID = 0; //The fragment shader id
};