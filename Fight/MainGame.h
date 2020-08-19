#pragma once
#include <sdl\SDL.h>
#include <GL\glew.h>
#include <winsock2.h>

#include "Window.h"
#include "Keyboard.h"
#include "Button.h"
#include "Player.h"
#include "WaveFrontOBJReader.h"
#include "Terrain.h"
#include "World.h"
#include "Client.h"
#include "Server.h"
#include "ThreadManager.h"
#include "PlanetTerrain.h"

/**
*
*	The objective of this class is to manage all of the other classes
*	and render everything for use.
*
*/

//State of the game
enum class GameState {
	MENU,
	HOST,
	PLAY,
	PAUSED,
	EXIT
};

enum class MenuState {
	NOTHING,
	PLAY,
	LOAD,
	MULTI,
	SINGLE,
	OPTIONS,
	LANGUAGE,
	EXIT
};

class MainGame
{
public:
	//Constructer and Deconstructer
	MainGame();
	~MainGame();

	
private:
	/*
		The menu screen launched at startup.
	*/
	void mainMenuLoop();

	/*
		Updates the games visuals and rerenders objects.
	*/
	void singleGameLoop();

	/*
		Gets data from server and renders objects.
	*/
	void multiGameLoop();

	/*
		Updates the game objects.
	*/
	void serverGameLoop();

	//Window settings.
	Window * n_window;			//The Window object.
	int n_screenWidth = 1280;	//Screen width.
	int n_screenHeight = 720;	//Screen height.

	//Objects.
	Player * n_player;
	ThreadManager n_threadManager;
	Client * n_client;
	Terrain n_terrain;							//Terrain.
	GameState n_gameState = GameState::MENU;	//The game state.
	MenuState n_menuState = MenuState::NOTHING; //The menu state.
	WaveFrontOBJReader n_loader;				//Object loader.
	Keyboard n_keyboard;						//The keyboard.
};