#pragma once
#include <vector>
#include <ctime>

#include "GLSLContext.h"
#include "Entity.h"
#include "Player.h"
#include "Model.h"

/*
	This class manages all of the entites in the world,
	simulating physics determening if they should be rendered
	and updating positions.

	Default: name = default, type = WORLD. 
*/

enum class Type
{
	WORLD,
	MAZE
};

class World
{
public:

	static unsigned int id;		//The number of worlds and the id of the last created world.

	/*
		Creates a world with a specific type and name.
		@param name
			This is the name of the world.
		@param type
			This is the type of the world (WORLD, MAZE).
		@param mass
			This is the mass of the planet in earths.
		@param radius
			This is the radius of the planet in earths.
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
	World(const char * name, Type type, float mass, float radius, const char * vertexShader, const char * fragmentShader, int numOfAttributes, const char * attributes[]);

	/*
		Creates a world with a specific name.
		@param name
			This is the name of the world.
		@param mass
			This is the mass of the planet in earths.
		@param radius
			This is the radius of the planet in earths.
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
	World(const char * name, float mass, float radius, const char * vertexShader, const char * fragmentShader, int numOfAttributes, const char * attributes[]);

	/*
		Creates a default world.
		@param mass
			This is the mass of the planet in earths.
		@param radius
			This is the radius of the planet in earths.
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
	World(float mass, float radius, const char * vertexShader, const char * fragmentShader, int numOfAttributes, const char * attributes[]);

	/*
		Cleans up worlds
	*/
	~World();

	/*
		Adds an entity into the world.
		@param entity
			The entity to be added to the world.
	*/
	void addEntity(Entity * entity);

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
		Removes a specific entity from the world.
		@param id
			The id of entity to be removed from the world.
	*/
	void removeEntity(unsigned int id);

	/*
		Set the world player to a player.
	*/
	void setPlayer(Player * player)
	{ 
		n_player = player;
	};

	/*
		Gets the player of the world.
	*/
	Player * getPlayer() 
	{
		return n_player;
	};

	/*
		Gets the radius of the planet in meters.
	*/
	float getRadius()
	{
		return n_radius;
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
	void damageEntity(Entity * attacker, Entity * defender, float amount);

	/*
		Updates positions and tests interactions.
	*/
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

	//Private variables
	const char * n_name;						//The name of the world.
	unsigned int n_id;							//The world ID.
	Player * n_player;							//The world player.
	std::vector<GLuint> n_uniformLocations;		//The locations of the uniform variables.
	std::vector<Entity*> n_staticEntities;		//All of the still entities in the world.
	std::vector<Entity*> n_dynamicEntities;		//All of the moving entities in the world.
	Type n_type;								//The world type.
	GLSLContext n_shaders;						//World shader.
	clock_t n_oldTime, n_currentTime;			//World timing.
	float n_mass;								//The mass of the planet in earths.
	float n_radius;								//The radius of the planet in earths.
	float n_gAcceleration;						//The acceleration of objects on the planet to the planet.
};

