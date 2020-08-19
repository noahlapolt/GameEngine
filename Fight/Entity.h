#pragma once
#include "Texture.h"
#include "Object.h"

enum class EntityMovment {
	DYNAMIC,
	STATIC
};

enum class EntityType {
	NEWE,
	CUBE
};

class Entity : public Object
{
public:
	Entity(GLuint vertexID, GLuint UVID, size_t vboSize, GLuint textureID, GLuint normalMapID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float mass, EntityType type, EntityMovment entityMovment);
	~Entity();

	//Public Functions
	void draw();

	EntityMovment getMovment() { return n_movment; };
	EntityType getType() { return n_type; };
	glm::mat4 getEntityMatrix()
	{
		return n_entityMatrix;
	};
	glm::vec3 getRotation()
	{
		return n_rotation;
	};
	glm::vec3 getScale() 
	{
		return n_scale;
	};

	void setRotation(glm::vec3 rotation)
	{
		n_rotation = rotation;
	};
	void setScale(glm::vec3 scale)
	{
		n_scale = scale;
	};
	void setVertexID(GLuint vertexID)
	{
		n_vbo = vertexID;
	};
	void setUVID(GLuint UVID)
	{
		n_ubo = UVID
;
	};
	void setVBOSize(size_t vboSize)
	{
		n_vboSize = vboSize;
	};

private:
	//Private Variables
	glm::vec3 n_rotation, n_scale;								//The direction the model is looking.
	GLuint n_vbo, n_ubo, n_textureID, n_normalMapID;	//GL data location
	EntityType n_type;
	EntityMovment n_movment;
	glm::mat4 n_entityMatrix;
	size_t n_vboSize;
};

