#include "Keyboard.h"

bool Keyboard::n_keys[] = { false };
bool Keyboard::n_mouseButtons[] = { false };
MousePos Keyboard::n_pos = { 0, 0 };

/*
	Returns true if the mouse button was pressed then released.
	
	@param button
		The button being tested.
*/
bool Keyboard::isButtonClicked(int button) {
	bool clicked = false;


	if (isButtonDown(button)) {
		n_buttonDown = button;
	}
	else if (n_buttonDown == button) {
		clicked = true;
		n_buttonDown = -1;
	}

	return clicked;
}

/*
	Returns true if the key is pressed then released.

	@param key
		the key to check.
*/
bool Keyboard::isKeyClicked(int key) {
	bool clicked = false;

	if (isKeyDown(key)) {
		n_keyDown = key;
	}
	else if (n_keyDown == key) {
		clicked = true;
		n_keyDown = -1;
	}

	return clicked;
}

/*
	Processes if a mouse button or key is up or down and updates mouse position.
*/
void Keyboard::process() {
	//The event loop
	while (SDL_PollEvent(&n_event)) {
		switch (n_event.type) {
			case SDL_QUIT:
				system("exit");
				break;
			case SDL_MOUSEBUTTONDOWN:
				n_mouseButtons[n_event.button.button] = true;
				break;
			case SDL_MOUSEBUTTONUP:
				n_mouseButtons[n_event.button.button] = false;
				break;
			case SDL_MOUSEMOTION:
				n_pos.x = n_event.motion.x;
				n_pos.y = n_event.motion.y;
				break;
			case SDL_KEYDOWN:
				n_keys[n_event.key.keysym.scancode] = true;
				break;
			case SDL_KEYUP:
				n_keys[n_event.key.keysym.scancode] = false;
				break;
		}
	}
}