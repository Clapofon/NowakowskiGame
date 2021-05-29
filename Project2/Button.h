#pragma once

#include <SDL.h>
#include "Text.h"

class Button
{
public:

	Button(std::string font, int size, SDL_Color color, std::string message, glm::vec2 pos, glm::vec2 dims, SDL_Color backgroundColor);
	Button(std::string font, int size, SDL_Color color, std::string message, glm::vec2 pos, glm::vec2 dims, SDL_Color backgroundColor, bool overlay);
	~Button();

	void update();
	void draw();

	SDL_Rect getRect(int buttonId);

	void setOverlay(bool overlay);

private:

	SDL_Rect m_dstRect;
	SDL_Color m_color;

	Text* m_text;

	glm::vec2 m_position;
	glm::vec2 m_dimentions;

	bool m_isOverlay;

	float m_counter;
};

