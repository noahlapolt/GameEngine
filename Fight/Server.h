#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <WS2tcpip.h>

#include "Object.h"

#pragma comment (lib, "ws2_32.lib")

class Server
{
public: 

	/*
		Creates a server.
	*/
	Server();

	~Server();

	void query();

	/*
		Adds an object into the world.
		@param object
			The object to be added to the world.
	*/
	void addObject(Object * object);

	/*
		Removes a specific entity from the world.
		@param id
			The id of object to be removed from the world.
	*/
	void removeObject(unsigned int id);

	/*
		Inflicts a certain amount of damage to an object.
		@param attacker
			The object dealing damage.
		@param defender
			The object taking damage.
		@param amount
			The amount of damage taken by the defender.
	*/
	void damageObject(Object * attacker, Object * defender, float amount);

private:
	SOCKET n_clientSocket;
	char n_buf[4096];

	std::vector<Object*> n_objects;
};

