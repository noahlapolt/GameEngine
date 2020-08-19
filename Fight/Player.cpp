#include "Player.h"

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
Player::Player(GLuint vertexID, GLuint UVID, size_t vboSize, GLuint textureID, GLuint normalTextureID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float mass,
	double health, int screenWidth, int screenHeight, float viewDistance, float viewAngle, EntityType type, EntityMovment movment)
	: Entity(vertexID, UVID, vboSize, textureID, normalTextureID, position, rotation, scale, mass, type, movment)
{
	n_health = health;
	n_screenWidth = screenWidth;
	n_screenHeight = screenHeight;
	n_persMatrix = glm::perspective(glm::radians(viewAngle), (float)screenWidth / (float)screenHeight, 0.1f, viewDistance);
	update();
}

//Deconstructor
Player::~Player()
{
}

/*
	Updates the player and camera.
*/
void Player::update() {
	gameInput();
	updateCamera();
}

/*
	Updates the camera's rotation.
*/
bool Player::updateCamera() {
	//The direction the player is looking
	glm::vec3 direction(cos(getRotation().x) * sin(getRotation().y), sin(getRotation().x), cos(getRotation().x) * cos(getRotation().y));

	//Movment left and right
	glm::vec3 right = glm::vec3(sin(getRotation().y - 3.14f / 2.0f), 0, cos(getRotation().y - 3.14f / 2.0f));

	//The up vector y
	glm::vec3 up = glm::cross(right, direction);

	//The view matrix
	n_playerMatrix = glm::lookAt(getPosition(), getPosition() + direction, up);

	//Always return false because the update has happened
	return false;
}

/*
	Gets the input from keyboard and mouse and updates the player's location.
*/
void Player::gameInput() {
	n_keyboard.process();

	//Changes the angle based on mouse movment
	setRotation(glm::vec3(getRotation().x, getRotation().y + n_mouseSpeed * float(((n_screenWidth / 2 - n_keyboard.getMousePos().x))), getRotation().z));
	setRotation(glm::vec3(getRotation().x + n_mouseSpeed * float(((n_screenHeight / 2 - n_keyboard.getMousePos().y))), getRotation().y, getRotation().z));

	/*Tests what key is pressed*/
	if (n_keyboard.isKeyDown(SDL_SCANCODE_W)) {
		//Moves position based on camera rotation and last position
		setPosition(getPosition() + glm::vec3(sin(getRotation().y), 0, cos(getRotation().y)) * n_playerSpeed);
	}
	else if (n_keyboard.isKeyDown(SDL_SCANCODE_S)) {
		//Moves position based on camera rotation and last position
		setPosition(getPosition() - glm::vec3(sin(getRotation().y), 0, cos(getRotation().y)) * n_playerSpeed);
	}
	if (n_keyboard.isKeyDown(SDL_SCANCODE_A)) {
		//Moves position based on camera rotation and last position
		setPosition(getPosition() - glm::vec3(sin(getRotation().y - n_PI / 2.0f), 0, cos(getRotation().y - n_PI / 2.0f)) * n_playerSpeed);
	}
	else if (n_keyboard.isKeyDown(SDL_SCANCODE_D)) {
		//Moves position based on camera rotation and last position
		setPosition(getPosition() + glm::vec3(sin(getRotation().y - n_PI / 2.0f), 0, cos(getRotation().y - n_PI / 2.0f)) * n_playerSpeed);
	}

	if (n_keyboard.isKeyDown(SDL_SCANCODE_SPACE)) {
		setPosition(getPosition() + glm::vec3(0.0f, n_playerSpeed, 0.0f));
	}
	else if (n_keyboard.isKeyDown(SDL_SCANCODE_LCTRL)) {
		setPosition(getPosition() + glm::vec3(0.0f, -n_playerSpeed, 0.0f));
	}

}