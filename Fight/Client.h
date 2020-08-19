#pragma once
#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <WS2tcpip.h>

#include "Model.h"
#include "Player.h"
#include "GLSLContext.h"
#include "WaveFrontOBJReader.h"

#pragma comment(lib, "ws2_32.lib")

class Client
{
public:
	/*
		Creates a default world.
		@param player
			The player in the world.
		@param vertexShader
			The file path of the vertex shader.
		@param fragmentShader
			The file path of the fragment shader.
		@param numOfAttributes
			The number of attributes to be added.
		@param attributes
			The attributes to be added.
	*/
	Client(std::string ipAddress, const char * vertexShader, const char * fragmentShader, int numOfAttributes, const char * attributes[]);

	~Client();

	/*
		Sets up uniform variable locations.
		@param uniformVariable
			The name of the uniform varibale to find.
	*/
	void addUniformVariableLocation(const char * uniformVariable)
	{
		n_uniformLocations.push_back(n_shaders.getUniformLocation(uniformVariable));
	}

	/*
		Set the world player to a player.
	*/
	void setPlayer(Player * player)
	{
		n_player = player;
	};

	void update();

	/*
		Draws the scene.
		@param player
			The player that the scene should be drawn for.
	*/
	void draw();

private:
	/*
		Creates and compiles the shader files.
		@param vertex
			The file path of the vertex shader.
		@param fragment
			The file path of the fragment shader.
		@param numOfAttributes
			The number of attributes to be added.
		@param attributes
			The name of the attributes to be added.
	*/
	void initShaders(const char * vertex, const char * fragment, int numOfAtrributes, const char * attributes[]);

	char n_buf[4096];
	SOCKET n_sock;

	Player * n_player;							//The world player.
	WaveFrontOBJReader n_loader;
	std::vector<GLuint> n_uniformLocations;		//The locations of the uniform variables.
	std::vector<Entity*> n_staticEntities;		//All of the still entities in the world.
	std::vector<Entity*> n_dynamicEntities;		//All of the moving entities in the world.
	GLSLContext n_shaders;						//World shader.
};

