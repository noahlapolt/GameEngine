#include "GLSLContext.h"
#include <vector>
#include <fstream>

void GLSLContext::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) {
	//Creates the id for the vertex shader
	n_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (n_vertexShaderID == 0) {
		printf("Error creating vertex shader");
	}

	//Creates the id for the fragment shader
	n_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (n_fragmentShaderID == 0) {
		printf("Error creating fragment shader");
	}

	//Compiles the shaders
	compileShader(vertexShaderFilePath, n_vertexShaderID);
	compileShader(fragmentShaderFilePath, n_fragmentShaderID);
}

void GLSLContext::addAttribute(const std::string& atribName) {
	//binds the attribute to the location
	glBindAttribLocation(n_programID, n_numAtrtibs++, atribName.c_str());
}

void GLSLContext::linkShaders() {
	//Creates the program id
	n_programID = glCreateProgram();

	//Attaches the shaders
	glAttachShader(n_programID, n_vertexShaderID);
	glAttachShader(n_programID, n_fragmentShaderID);

	//Links the program to the shaders
	glLinkProgram(n_programID);

	//A  variable that tests if the file is linked
	GLint isLinked = 0;
	//Tests if it is linked
	glGetProgramiv(n_programID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE) {
		//The max length
		GLint maxLength = 0;
		//Gets the max lengths
		glGetProgramiv(n_programID, GL_INFO_LOG_LENGTH, &maxLength);

		//Makes the text
		std::vector<char> errorLog(maxLength);
		//Gets error
		glGetProgramInfoLog(n_programID, maxLength, &maxLength, &errorLog[0]);

		//Deletes the program
		glDeleteProgram(n_programID);

		//Delets the shaders
		glDeleteShader(n_vertexShaderID);
		glDeleteShader(n_fragmentShaderID);

		//Prints error
		std::printf("%\n", &(errorLog[0]));
	}

	//Detaches everything
	glDetachShader(n_programID, n_vertexShaderID);;
	glDetachShader(n_programID, n_fragmentShaderID);
	glDeleteShader(n_vertexShaderID);
	glDeleteShader(n_fragmentShaderID);

}

GLint GLSLContext::getUniformLocation(const std::string& uniformName) {
	//Gets the location of uniform variable
	GLint location = glGetUniformLocation(n_programID, uniformName.c_str());
	if (location == GL_INVALID_INDEX) {
		printf("Error invalid uniform location. May have been optimized out.");
	}
	//Sends back the location
	return location;
}

void GLSLContext::use() {
	//Uses the program that was created
	glUseProgram(n_programID);
	for (int i = 0; i < n_numAtrtibs; i++) {
		//Enables attributs
		glEnableVertexAttribArray(i);
	}
}

void GLSLContext::unuse() {
	//Deletes the program
	glUseProgram(0);
	for (int i = 0; i < n_numAtrtibs; i++) {
		//Disables attributs
		glDisableVertexAttribArray(i);
	}
}

void GLSLContext::compileShader(const std::string& filePath, GLuint id) {
	//Takes in the file
	std::ifstream vertexFile(filePath);
	//Test if it opened
	if (vertexFile.fail()) {
		//Prints error
		perror(filePath.c_str());
		printf("Error failed to open file.");
	}

	//Emptys preivous contents and makes a singular line of code
	std::string fileContents = "";
	std::string line;

	//Fills file contents
	while (std::getline(vertexFile, line)) {
		fileContents += line + "\n";
	}

	//Closes file
	vertexFile.close();
	//Points to the location that the data is stored
	const char* contentsPtr = fileContents.c_str();

	//Uses shader source to compile
	glShaderSource(id, 1, &contentsPtr, nullptr);
	glCompileShader(id);

	//Tests if it was compiled successfully
	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		//Gets error message
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		//Error length
		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		//Deletes shader program
		glDeleteShader(id);

		//Prints error
		std::printf("%s\n", &(errorLog[0]));
	}
}