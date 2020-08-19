#include "World.h"

unsigned int World::id = 0;

/*
	Creates a world with a specific type and name.
	@param name
		This is the name of the world.
	@param type
		This is the type of the world (WORLD, MAZE).
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
World::World(const char * name, Type type, float mass, float radius, const char * vertexShader, const char * fragmentShader, int numOfAttributes, const char * attributes[])
{
	n_id = id;
	n_name = name;
	n_type = type;
	id++;
	n_oldTime = clock();
	n_mass = mass * 9903520300000000000000000000.0f;
	n_radius = radius * 8388608.0f;
	n_gAcceleration = 9.80665f * (mass / (radius * radius));
	initShaders(vertexShader, fragmentShader, numOfAttributes, attributes);
}

/*
	Creates a world with a specific name.
	@param name
		This is the name of the world.
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
World::World(const char * name, float mass, float radius, const char * vertexShader, const char * fragmentShader, int numOfAttributes, const char * attributes[])
{
	n_id = id;
	n_name = name;
	n_type = Type::WORLD;
	id++;
	n_oldTime = clock();
	n_mass = mass * 9903520300000000000000000000.0f;
	n_radius = radius * 8388608.0f;
	n_gAcceleration = 9.80665f * (mass / (radius * radius));
	initShaders(vertexShader, fragmentShader, numOfAttributes, attributes);
}

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
World::World(float mass, float radius, const char * vertexShader, const char * fragmentShader, int numOfAttributes, const char * attributes[])
{
	n_id = id;
	n_name = "default";
	n_type = Type::WORLD;
	id++;
	n_oldTime = clock();
	n_mass = mass * 9903520300000000000000000000.0f;
	n_radius = radius * 8388608.0f;
	//The ones are temporary should be radius
	n_gAcceleration = 9.80665f * (mass / (2 * 2));
	initShaders(vertexShader, fragmentShader, numOfAttributes, attributes);
}

/*
	Cleans up worlds
*/
World::~World() 
{
	n_staticEntities.clear();
	n_dynamicEntities.clear();
}

/*
	Adds an entity into the world.
	@param entity
		The entity to be added to the world.
*/
void World::addEntity(Entity * entity)
{
	if (entity->getMovment() == EntityMovment::DYNAMIC) {
		n_dynamicEntities.push_back(entity);
	}
	else if (entity->getMovment() == EntityMovment::STATIC) {
		n_staticEntities.push_back(entity);
	}
}

/*
	Removes a specific entity from the world.
	@param id
		The id of entity to be removed from the world.
*/
void World::removeEntity(unsigned int id)
{
	
}

/*
	Inflicts a certain amount of damage to an entity.
	@param attacker
		The entity dealing damage.
	@param defender
		The entity taking damage.
	@param amount
		The amount of damage taken by the defender.
*/
void World::damageEntity(Entity * attacker, Entity * defender, float amount)
{

}

/*
	Updates positions and tests interactions draws the scene.
*/
void World::draw()
{
	n_player->update();

	//Uniform variable defaults
	glm::vec3 lightPos = n_player->getPosition();

	//Clears the buffer
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	n_shaders.use();

	glm::mat4 perspectiveMatrix = n_player->getPerspectiveMatrix();
	glm::mat4 viewMatrix = n_player->getPlayerMatrix();
	glm::mat4 modelMatrix = n_player->getEntityMatrix();
	glm::mat4 mvp = perspectiveMatrix * viewMatrix * modelMatrix;

	glUniformMatrix4fv(n_uniformLocations[2], 1, GL_FALSE, &(viewMatrix[0][0]));

	for (Entity * dynamic : n_dynamicEntities) {
		//Value of uniform variables
		modelMatrix = dynamic->getEntityMatrix();
		mvp = perspectiveMatrix * viewMatrix * modelMatrix;
		
		//Sets the uniform variables
		glUniformMatrix4fv(n_uniformLocations[0], 1, GL_FALSE, &(mvp[0][0]));
		glUniformMatrix4fv(n_uniformLocations[1], 1, GL_FALSE, &(modelMatrix[0][0]));
		glUniform3f(n_uniformLocations[3], lightPos.x, lightPos.y, lightPos.z);
		glUniform1i(n_uniformLocations[4], 0);
		glUniform1i(n_uniformLocations[5], 1);

		//draws the object
		dynamic->draw();	
	}
	for (Entity * staticE : n_staticEntities) {
		//Value of uniform variables
		modelMatrix = staticE->getEntityMatrix();
		mvp = perspectiveMatrix * viewMatrix * modelMatrix;

		//Sets the uniform variables
		glUniformMatrix4fv(n_uniformLocations[0], 1, GL_FALSE, &(mvp[0][0]));
		glUniformMatrix4fv(n_uniformLocations[1], 1, GL_FALSE, &(modelMatrix[0][0]));
		glUniform3f(n_uniformLocations[3], lightPos.x, lightPos.y, lightPos.z);
		glUniform1i(n_uniformLocations[4], 0);
		glUniform1i(n_uniformLocations[5], 1);

		//draws the object
		staticE->draw();
	}

	n_shaders.unuse();
}

/*
	Updates positions and tests interactions no drawing.
*/
void World::update()
{
	n_currentTime = clock();

	double timePassed = (double)(n_currentTime - n_oldTime) / CLOCKS_PER_SEC;

	for (Entity * dynamic : n_dynamicEntities) {
		//move everything down speeding up at the gravitational acceleration.
		dynamic->setMagnitude(dynamic->getVelocity() * timePassed + 0.5 * n_gAcceleration * (timePassed * timePassed));
		dynamic->setVelocity(dynamic->getVelocity() + n_gAcceleration * timePassed);

		glm::vec3 position = dynamic->getPosition();

		glm::vec3 forceVectors = -position;

		glm::vec3 unitVector = glm::vec3(0.0f);
		if (position.x != 0.0f || position.y != 0.0f || position.z != 0.0f) {
			unitVector = glm::normalize(forceVectors);
		}

		dynamic->setForceDirection(unitVector);
		dynamic->update();
	}

	n_oldTime = n_currentTime;
}

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
void World::initShaders(const char * vertex, const char * fragment, int numOfAttributes, const char * attributes[]) {
	//Loads the shaders
	n_shaders.compileShaders(vertex, fragment);
	//Links all the shaders
	n_shaders.linkShaders();
	//Adds an attributes
	for (int i = 0; i < numOfAttributes; i++) {
		n_shaders.addAttribute(attributes[i]);
	}

	//A little consle output
	printf("Shaders initalized\n");
}