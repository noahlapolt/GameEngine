#pragma once

/**
* This class is used to create a player.
* The player is a child of object and has its own special attributs.
* Atributes:
*	health
*
* This class also creates a camera to go with the player.
*/

//Includes for math
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

//The objects parent
#include "Entity.h"
#include "Keyboard.h"

//Player Class parent is object
class Player : public Entity
{
public:
	/*
	Creates a player.

	@param vertices
		The model data.
	@param uvs
		The texture mapping data.
	@param texture
		The color data to be rendered.
	@param normalTex
		The texture that holds the objects normals.
	@param position
		The location of the model and viewspace.
	@param rotation
		The rotation of the model and the viewspace.
	@param scale
		The scale of the model.
	@param mass
		The mass of the objecct.
	@param velocity
		The speed the player is going in the direction the player is looking.
	@param health
		The amount of health the player has.
	@param screenWidth
		The width of the window.
	@param screenHeight
		The height of the window.
	@param viewDistance
		The furthest distance an object will be rendered for a player.
	@param viewAngle
		The field of vision of the player.

*/
	Player(GLuint vertexID, GLuint UVID, size_t vboSize, GLuint textureID, GLuint normalTextureID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float mass,
		double health, int screenWidth, int screenHeight, float viewDistance, float viewAngle, EntityType type, EntityMovment movment);

	//Deconstructer
	~Player();

	//Getters
	glm::mat4 getPlayerMatrix()
	{
		return n_playerMatrix;
	};
	glm::mat4 getPerspectiveMatrix()
	{
		return n_persMatrix;
	};
	double getHealth()
	{
		return n_health;
	};
	int getScreenWidth() { return n_screenWidth; };
	int getScreenHeight() { return n_screenHeight; };

	//Setters
	void setHealth(double newHealth)
	{
		n_health = newHealth;
	};

	/*
		Updates the player and camera.
	*/
	void update();

private:
	/*
		Updates the camera's rotation.
	*/
	bool updateCamera();

	/*
		Gets the input from keyboard and mouse and updates the player's location.
	*/
	void gameInput();

	//Private Variables
	float n_mouseSpeed = 0.001f; //Speed the mouse moves.
	float n_playerSpeed = 0.5f;  //The speed the player moves.
	const float n_PI = 3.1415927f; //PI
	glm::mat4 n_playerMatrix, n_persMatrix = glm::mat4(1.0f);
	double n_health;
	int n_screenWidth, n_screenHeight;
	Keyboard n_keyboard;
};