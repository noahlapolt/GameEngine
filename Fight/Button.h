#pragma once

#include "GUI.h"
#include "Keyboard.h"

class Button : public GUI
{
public:
	Button(GLuint textureID, glm::vec2 position, glm::vec2 scale, float rotation);
	~Button();

	bool leftClicked() { return n_leftClicked && n_onButton;  };
	bool rightClicked() { return n_leftClicked && n_onButton; };
	void draw();

private:
	Keyboard n_keyboard;
	bool n_onButton = false;
	bool n_leftClicked = false;
	bool n_rightClicked = false;
};