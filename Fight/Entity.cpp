#include "Entity.h"

Entity::Entity(GLuint vertexID, GLuint UVID, size_t vboSize, GLuint textureID, GLuint normalMapID,
	glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float mass,
	EntityType type, EntityMovment entityMovment) :
	Object(position, glm::vec3(0.0f), mass, 0.0f)
{
	n_movment = entityMovment;
	n_type = type;
	n_textureID = textureID;
	n_normalMapID = normalMapID;
	n_vbo = vertexID;
	n_ubo = UVID;
	n_vboSize = vboSize;
	n_rotation = rotation;
	n_scale = scale;
}


Entity::~Entity()
{
}

void Entity::draw()
{
	//Makes the object matrix
	glm::mat4 objectMatrix = glm::mat4(1.0f);

	//Its translation
	glm::mat4 translation = glm::translate(objectMatrix, getPosition());

	//Its rotation
	glm::mat4 rotationX = glm::rotate(objectMatrix, n_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotationY = glm::rotate(objectMatrix, n_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rotationZ = glm::rotate(objectMatrix, n_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

	//Scale
	glm::mat4 newScale = glm::scale(objectMatrix, n_scale);

	//Adds it to the list
	n_entityMatrix = (translation * rotationX * rotationY * rotationZ * newScale);


	//Binds textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, n_textureID);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, n_normalMapID);

	//Binds the object to the first buffer	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, n_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Binds the texture uvs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, n_ubo);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//Draws the triangles
	glDrawArrays(GL_TRIANGLES, 0, n_vboSize);

	//Disables the first vertex
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	//Unbinds the object from the first buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}
