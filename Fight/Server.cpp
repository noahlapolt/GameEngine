#include "Server.h"

/*
	Creates a server and the default world.
*/
Server::Server() 
{
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0)
	{
		std::cerr << "Can't Inint winsock!\n";
	}

	//Create a socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		std::cerr << "Can't create socket!\n";
	}
	else
	{
		printf("Server Online\n");
	}

	//Bind the ip address and port to a socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(listening, (sockaddr*)&hint, sizeof(hint));

	//Tell windsock the socket is listening
	listen(listening, SOMAXCONN);

	//Wait for a connection
	sockaddr_in client;
	int clientSize = sizeof(client);

	n_clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

	char host[NI_MAXHOST];
	char service[NI_MAXSERV];

	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXSERV);

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	{
		std::cout << host << " connected on port " << service << std::endl;
	}
	else
	{
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		std::cout << host << " connected on port " <<
			ntohs(client.sin_port) << std::endl;
	}

	//Close listening socket
	closesocket(listening);
}

Server::~Server()
{
	//Close the socket
	closesocket(n_clientSocket);

	//Cleanup winsock
	WSACleanup();
}

/*
	Adds an object into the world.
	@param object
		The object to be added to the world.
*/
void Server::addObject(Object * object)
{
	n_objects.push_back(object);
}

/*
	Removes a specific object from the world.
	@param id
		The id of object to be removed from the world.
*/
void Server::removeObject(unsigned int id)
{

}

/*
	Inflicts a certain amount of damage to an entity.
	@param attacker
		The object dealing damage.
	@param defender
		The object taking damage.
	@param amount
		The amount of damage taken by the defender.
*/
void Server::damageObject(Object * attacker, Object * defender, float amount)
{

}

/*
	Updates positions and tests interactions no drawing.
*/
void Server::query() {
	for (Object * object : n_objects) {
		//Update objects

		//Get data from client
		ZeroMemory(n_buf, 4096);
		int bytesReceived = recv(n_clientSocket, n_buf, 4096, 0);
		if (bytesReceived > 0)
		{
			std::string data = std::string(n_buf, 0, bytesReceived);

			if (data == "NE") {
				std::string numEntities = std::to_string(n_objects.size());
				send(n_clientSocket, numEntities.c_str(), (int)numEntities.length(), 0);
			}
		}

		//Send object data
		//send(n_clientSocket, all.c_str(), (int)all.length(), 0);
	}

	/* This is to get data from client
	//ZeroMemory(n_buf, 4096);

	//Wait for client to send data
	//int bytesReceived = recv(n_clientSocket, n_buf, 4096, 0);
	//if (bytesReceived == SOCKET_ERROR)
	//{
	//	std::cerr << "Error in recv()\n";
	//}

	//if (bytesReceived == 0)
	//{
	//	std::cout << "Client disconnected\n";
	//}

	//std::string word = std::string(n_buf, 0, bytesReceived);

	//std::cout << word << std::endl;
	*/
}