#pragma once
#include <sdl\SDL.h>

//The x and y position of the mouse.
struct MousePos {
	int x = 0;
	int y = 0;
};

/*
	This class represents the active keyboard and mouse as an array of true or false variables.
	Tracks the position of the mouse when it is moved.
*/
class Keyboard
{
public:
	static bool n_keys[SDL_NUM_SCANCODES];		//The true or false key map.
	static bool n_mouseButtons[4];				//The true or false mouse button map.
	static MousePos n_pos;						//The position of the mouse.

	/*
		Returns true if the mouse button is down and false if it is up.
		
		@param button
			The button being tested.
	*/
	bool isButtonDown(int button) { return n_mouseButtons[button]; };

	/*
		Gets the current location of the mouse.
	*/
	MousePos getMousePos() { return n_pos; };

	/*
		Returns true if the key is down and false if it is up.

		@param key
			The key to check.
	*/
	bool isKeyDown(int key) { return n_keys[key]; };

	/*
		Returns true if the mouse button was pressed then released.

		@param button
			The button being tested.
	*/
	bool isButtonClicked(int button);

	/*
		Returns true if the key is pressed then released.

		@param key
			The key to check.
	*/
	bool isKeyClicked(int key);

	/*
		Processes if a mouse button or key is up or down and updates mouse position.
	*/
	void process();

private:
	SDL_Event n_event;					//The keyboard event.
	int n_buttonDown = -1;				//The button that is currently down.
	int n_keyDown = -1;					//The key that is currently down.
};

