#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>

#include <stdio.h>

//Some flags
enum WindowFlags { INVISABLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

/*
	Creates a simple SDL window and some useful functions.
*/
class Window
{
public:
	Window(const char *windowName, int screenWidth, int screenHeight, unsigned int currentFlags);
	~Window();

	/*
		Switches to the next screen.
	*/
	void swapBuffer();

	/*
		Gets the pixel width of the screen.
	*/
	int getScreenWidth() { return n_screenWidth; };

	/*
		Gets the pixel height of the screen.
	*/
	int getScreenHeight() { return n_screenHeight; };

	/*
		Gets the SDL window object.
	*/
	SDL_Window* getWindow() { return n_sdlWindow; };

private:
	SDL_Window* n_sdlWindow;	//The window.

	int n_screenWidth = 1280;	//Screen width;
	int n_screenHeight = 720;	//Screen height;

};