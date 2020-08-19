#include "MainGame.h"

MainGame::MainGame()
{
	//Turns on all functions of sdl
	SDL_Init(SDL_INIT_EVERYTHING);

	//Creates a buffer in the first atrib
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//Creates the openGL context
	n_window = new Window("Lost", n_screenWidth, n_screenHeight, 0);

	//Updates game graphics
	mainMenuLoop();
}

MainGame::~MainGame()
{
	delete n_window;
}

/*
	The menu screen launched at startup.
*/
void MainGame::mainMenuLoop() {
	glClearColor(0.99f, 0.81f, 0.89f, 1.0f);

	//Textures
	Texture backgroundTex("Data/background.png");
	Texture playTex("Data/playButton.png");
	Texture optionsTex("Data/optionsButton.png");
	Texture createTex("Data/playButton.png");
	Texture loadTex("Data/playButton.png");
	Texture singleTex("Data/singleButton.png");
	Texture multiTex("Data/multiButton.png");
	Texture hostTex("Data/hostButton.png");
	Texture joinTex("Data/joinButton.png");
	Texture exitTex("Data/exitButton.png");
	Texture backTex("Data/backButton.png");
	Texture loadingTex("Data/playButton.png");

	//Background
	GUI background(backgroundTex.getTextureID(), glm::vec2(640.0f, 360.0f), glm::vec2(1280.0f, 720.0f), 0.0f);
	
	//Main Menu
	Button play(playTex.getTextureID(), glm::vec2(640.0f, 240.0f), glm::vec2(320.0f, 100.0f), 0.0f);
	Button options(optionsTex.getTextureID(), glm::vec2(640.0f, 360.0f), glm::vec2(320.0f, 100.0f), 0.0f);

	//Play Options
	Button create(createTex.getTextureID(), glm::vec2(640.0f, 240.0f), glm::vec2(320.0f, 100.0f), 0.0f);
	Button load(loadTex.getTextureID(), glm::vec2(640.0f, 360.0f), glm::vec2(320.0f, 100.0f), 0.0f);
	Button single(singleTex.getTextureID(), glm::vec2(640.0f, 240.0f), glm::vec2(320.0f, 100.0f), 0.0f);
	Button multi(multiTex.getTextureID(), glm::vec2(640.0f, 360.0f), glm::vec2(320.0f, 100.0f), 0.0f);


	//Multi Options
	Button join(joinTex.getTextureID(), glm::vec2(640.0f, 240.0f), glm::vec2(320.0f, 100.0f), 0.0f);
	Button host(hostTex.getTextureID(), glm::vec2(640.0f, 360.0f), glm::vec2(320.0f, 100.0f), 0.0f);

	//Utilites
	Button exit(exitTex.getTextureID(), glm::vec2(640.0f, 480.0f), glm::vec2(320.0f, 100.0f), 0.0f);
	Button back(backTex.getTextureID(), glm::vec2(640.0f, 480.0f), glm::vec2(320.0f, 100.0f), 0.0f);
	GUI loading(loadingTex.getTextureID(), glm::vec2(640.0f, 360.0f), glm::vec2(320.0f, 100.0f), 0.0f);

	while (n_gameState == GameState::MENU) {
		glClearDepth(1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		n_keyboard.process();

		if (n_menuState == MenuState::NOTHING) {
			if (play.leftClicked()) {
				n_menuState = MenuState::PLAY;
			}
			if (options.leftClicked()) {
				n_menuState = MenuState::OPTIONS;
			}
			if (exit.leftClicked()) {
				n_gameState = GameState::EXIT;
			}
			if (n_keyboard.isKeyDown(SDL_SCANCODE_ESCAPE)) {
				n_gameState = GameState::EXIT;
			}

			play.draw();
			options.draw();
			exit.draw();
		}
		else if (n_menuState == MenuState::PLAY) {
			if (create.leftClicked()) {
				n_menuState = MenuState::LOAD;
			}
			if (load.leftClicked()) {
				n_menuState = MenuState::LOAD;
			}
			if (back.leftClicked()) {
				n_menuState = MenuState::NOTHING;
			}

			create.draw();
			load.draw();
			back.draw();
		}
		else if (n_menuState == MenuState::LOAD) {
			if (single.leftClicked()) {
				n_gameState = GameState::PLAY;
				n_menuState = MenuState::SINGLE;
			}
			if (multi.leftClicked()) {
				n_menuState = MenuState::MULTI;
			}
			if (back.leftClicked()) {
				n_menuState = MenuState::PLAY;
			}

			single.draw();
			multi.draw();
			back.draw();
		}
		else if (n_menuState == MenuState::MULTI) {
			if (host.leftClicked()) {
				n_gameState = GameState::HOST;
				serverGameLoop();
			}
			if (join.leftClicked()) {
				n_gameState = GameState::PLAY;
				multiGameLoop();
			}
			if (back.leftClicked()) {
				n_menuState = MenuState::LOAD;
			}

			host.draw();
			join.draw();
			back.draw();
		}

		//Background
		background.draw();

		//moves to the next window
		n_window->swapBuffer();
	}

	if (n_gameState == GameState::PLAY)
	{
		if (n_menuState == MenuState::SINGLE)
		{
			singleGameLoop();
		}
		else if (n_menuState == MenuState::MULTI)
		{
			multiGameLoop();
		}
	}
	else if (n_gameState == GameState::HOST)
	{
		serverGameLoop();
	}
}

/*
	Updates the games visuals and rerenders objects.
*/
void MainGame::singleGameLoop() {
	//World
	const char * atribs[] = { "vertexPosition", "vertexUV" };
	World world(1.0f, 0.00005f, "Shaders/vertexShader.vert", "Shaders/fragmentShader.frag", 2, atribs);

	//Hides cursor
	SDL_ShowCursor(SDL_DISABLE);

	n_terrain.generateTerrain();

	//Textures
	Texture playerTexture("Data/white.png");
	Texture mazeTexture("Data/wall.png");

	//Normal Textures
	Texture mazeNTexture("Data/wallN.png");

	//Models
	n_loader.loadOBJ("Data/cube.obj");
	Model cube(n_loader.getVertices(), n_loader.getUVs());
	Model terrianM(n_terrain.getTerrainVerts(), n_terrain.getTerrainUVs());

	//Entites
	n_player = new Player(cube.getVertexBuffer(), cube.getUVBuffer(), cube.getVBOSize(), playerTexture.getTextureID(), mazeNTexture.getTextureID(), glm::vec3(0.0f, world.getRadius(), 0.0f), glm::vec3(0.0f), glm::vec3(0.5f, 1.0f, 0.5f), 10, 100, n_screenWidth, n_screenHeight, 1000.0f, 45.0f, EntityType::NEWE, EntityMovment::DYNAMIC);
	Entity * terrain = new Entity(terrianM.getVertexBuffer(), terrianM.getUVBuffer(), terrianM.getVBOSize(), playerTexture.getTextureID(), mazeNTexture.getTextureID(), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f), 0.0f, EntityType::NEWE, EntityMovment::STATIC);

	//Fill world.
	world.addEntity(terrain);
	world.setPlayer(n_player);

	world.addUniformVariableLocation("MVP");
	world.addUniformVariableLocation("M");
	world.addUniformVariableLocation("V");
	world.addUniformVariableLocation("LightPosition_worldspace");
	world.addUniformVariableLocation("textureMap");
	world.addUniformVariableLocation("normalMap");

	//Stress tester
	srand(time(NULL));
	for (int i = 0; i < 0; i++) {
		int min = -500;
		int max = 1000;
		float density = 1.0f;
		glm::vec3 pos = glm::vec3(0 * ((rand() % max) + min) * density, ((rand() % max) + min) * density, ((rand() % max) + min) * density);
		Entity * tester = new Entity(cube.getVertexBuffer(), cube.getUVBuffer(), cube.getVBOSize(), playerTexture.getTextureID(), mazeNTexture.getTextureID(), pos, glm::vec3(0.0f), glm::vec3(1.0f), 0.0f, EntityType::NEWE, EntityMovment::DYNAMIC);
		world.addEntity(tester);
	}

	Entity * tester = new Entity(cube.getVertexBuffer(), cube.getUVBuffer(), cube.getVBOSize(), playerTexture.getTextureID(), mazeNTexture.getTextureID(), glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f), 0.0f, EntityType::NEWE, EntityMovment::STATIC);
	world.addEntity(tester);

	//Background color
	glClearColor(0.99f, 0.81f, 0.89f, 1.0f);

	bool updateDone = false;

	//Updates the world entities on another thread.
	n_threadManager.addThread([&](World * world) {
		while (n_gameState != GameState::EXIT) {
			if (n_gameState != GameState::PAUSED) {
				world->update();
			}
		}
		updateDone = true;
	}, &world);

	PlanetTerrain planetTerrain(glm::vec3(0.0f), world.getRadius(), 1, 5);

	//Jope works
	world.addEntity(planetTerrain.planetEntity);

	while (n_gameState != GameState::EXIT && !updateDone)
	{
		n_keyboard.process();

		if (n_keyboard.isKeyDown(SDL_SCANCODE_ESCAPE)) {
			n_gameState = GameState::EXIT;
		}
		if (n_keyboard.isKeyClicked(SDL_SCANCODE_I)) {
			if (n_gameState == GameState::PLAY) {
				SDL_ShowCursor(SDL_ENABLE);
				n_gameState = GameState::PAUSED;
			}
			else {
				SDL_ShowCursor(SDL_DISABLE);
				n_gameState = GameState::PLAY;
			}
		}

		//Locks mouse in the center of the screen
		if (n_gameState != GameState::PAUSED) {
			SDL_WarpMouseInWindow(n_window->getWindow(), n_screenWidth / 2, n_screenHeight / 2);

			planetTerrain.updateCunk(n_player->getPosition(), n_player->getRotation().y);

			world.draw();
		}

		//moves to the next window
		n_window->swapBuffer();
	}
}

/*
	Gets data from server and renders objects.
*/
void MainGame::multiGameLoop()
{
	std::string ipAddress;
	printf("IP-> \n");
	std::getline(std::cin, ipAddress);
	const char * atribs[] = { "vertexPosition", "vertexUV" };
	Client client(ipAddress, "Shaders/vertexShader.vert", "Shaders/fragmentShader.frag", 2, atribs);
	
	//Objects
	Texture playerTexture("Data/white.png");
	Texture mazeNTexture("Data/wallN.png");
	Model cube(n_loader.getVertices(), n_loader.getUVs());
	n_player = new Player(cube.getVertexBuffer(), cube.getUVBuffer(), cube.getVBOSize(), playerTexture.getTextureID(), mazeNTexture.getTextureID(), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.5f, 1.0f, 0.5f), 10, 100, n_screenWidth, n_screenHeight, 1000.0f, 45.0f, EntityType::NEWE, EntityMovment::DYNAMIC);
	
	client.setPlayer(n_player);

	client.addUniformVariableLocation("MVP");
	client.addUniformVariableLocation("M");
	client.addUniformVariableLocation("V");
	client.addUniformVariableLocation("LightPosition_worldspace");
	client.addUniformVariableLocation("textureMap");
	client.addUniformVariableLocation("normalMap");

	//Hides cursor
	SDL_ShowCursor(SDL_DISABLE);

	while (n_gameState != GameState::EXIT)
	{
		n_keyboard.process();

		if (n_keyboard.isKeyDown(SDL_SCANCODE_ESCAPE)) {
			n_gameState = GameState::EXIT;
		}
		if (n_keyboard.isKeyClicked(SDL_SCANCODE_I)) {
			if (n_gameState == GameState::PLAY) {
				SDL_ShowCursor(SDL_ENABLE);
				n_gameState = GameState::PAUSED;
			}
			else {
				SDL_ShowCursor(SDL_DISABLE);
				n_gameState = GameState::PLAY;
			}
		}

		//Locks mouse in the center of the screen
		if (n_gameState != GameState::PAUSED) {
			SDL_WarpMouseInWindow(n_window->getWindow(), n_screenWidth / 2, n_screenHeight / 2);
			
			client.update();
			client.draw();
		}

		//moves to the next window
		n_window->swapBuffer();
	}
}

/*
	Updates the game objects.
*/
void MainGame::serverGameLoop()
{
	SDL_Quit();
	Server server;

	for (int i = 0; i < 10; i++)
	{
		server.addObject(new Object(glm::vec3(i), glm::vec3(1.0f, 0.4f, 5.9f), 0.0f, 1.0f));
	}

	do 
	{
		n_keyboard.process();
		server.query();
	} while(!n_keyboard.isKeyDown(SDL_SCANCODE_ESCAPE));
}