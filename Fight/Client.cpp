#include "Client.h"

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
Client::Client(std::string ipAddress, const char * vertexShader, const char * fragmentShader, int numOfAttributes, const char * attributes[]) 
{
	int port = 54000;							//Listening port # of the server

	//Initialize winsock
	WSADATA data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		std::cerr << "Can't start winsock.\n";
	}

	//Create socket
	n_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (n_sock == INVALID_SOCKET)
	{
		std::cerr << "Can't create socket!\n";
	}

	//Fill in a hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	//Connect to server
	int connResult = connect(n_sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		std::cerr << "Can't connect to server\n";
	}

	initShaders(vertexShader, fragmentShader, numOfAttributes, attributes);

	n_loader.loadOBJ("Data/cube.obj");
	Texture playerTexture("Data/white.png");
	Texture mazeNTexture("Data/wallN.png");
	Model cube(n_loader.getVertices(), n_loader.getUVs());

	//Request the number of entities there ids and types
	int numEntities = 0;
	send(n_sock, "NE", 2, 0);

	//Wait for response
	ZeroMemory(n_buf, 4096);
	int bytesReceived = recv(n_sock, n_buf, 4096, 0);
	if (bytesReceived > 0)
	{
		std::string data = std::string(n_buf, 0, bytesReceived);
		numEntities = std::stoi(data);
	}
	else
	{
		printf("Error: failed to get number of entities on the server\n");
	}

	for (int i = 0; i < numEntities; i++) {
		n_dynamicEntities.push_back(new Entity(cube.getVertexBuffer(), cube.getUVBuffer(), cube.getVBOSize(), playerTexture.getTextureID(), playerTexture.getTextureID(), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f), 0.0f, EntityType::NEWE, EntityMovment::STATIC));
	}
}


Client::~Client()
{
	//Close everything
	closesocket(n_sock);
	WSACleanup();
	n_dynamicEntities.clear();
	n_staticEntities.clear();
	n_uniformLocations.clear();
}


void Client::update()
{
	//Send player info.
	for (Entity * dynamic : n_dynamicEntities) {

	}

	/* Get data
	//Wait for response
	ZeroMemory(n_buf, 4096);
	int bytesReceived = recv(n_sock, n_buf, 4096, 0);
	if (bytesReceived > 0)
	{
		std::string all = std::string(n_buf, 0, bytesReceived);
	}
	*/
}

/*
	Updates positions and tests interactions draws the scene.
*/
void Client::draw()
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

	n_shaders.unuse();
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
void Client::initShaders(const char * vertex, const char * fragment, int numOfAttributes, const char * attributes[]) {
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