#include "Button.h"

Button::Button(GLuint textureID, glm::vec2 position, glm::vec2 scale, float rotation) :
	GUI(textureID, position, scale, rotation)
{
}

Button::~Button()
{
}

void Button::draw()
{
	MousePos pos = n_keyboard.getMousePos();

	if (pos.x >= (getPosition().x - getScale().x / 2.0f) &&
		pos.x <= (getPosition().x + getScale().x / 2.0f) &&
		pos.y >= (getPosition().y - getScale().y / 2.0f) &&
		pos.y <= (getPosition().y + getScale().y / 2.0f))
	{
		n_onButton = true;
		setHover(glm::vec4(0.4f, 0.4f, 0.4f, 0.0f));
	}
	else {
		n_onButton = false;
		setHover(glm::vec4(0.0f));
	}

	n_leftClicked = n_keyboard.isButtonClicked(1);
	n_rightClicked = n_keyboard.isButtonClicked(2);

	GUI::draw();
}
