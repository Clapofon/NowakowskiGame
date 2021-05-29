#pragma once

#include <SDL.h>
#include <vector>
#include "Button.h"

class Menu
{
public:
	Menu(std::string tex, glm::vec2 srcDims, glm::vec2 dstDims);
	~Menu();

	void update();
	void draw();
	void addButton(std::string font, int size, SDL_Color color, std::string message, glm::vec2 pos, glm::vec2 dims, SDL_Color backgroundColor);
	void addButton(std::string font, int size, SDL_Color color, std::string message, glm::vec2 pos, glm::vec2 dims, SDL_Color backgroundColor, bool overlay);
	void addText(std::string font, int size, SDL_Color color, std::string message, glm::vec2 pos);
	void addText(std::string font, int size, SDL_Color color, std::string message, glm::vec2 pos, int wrapWidth);


	SDL_Rect getButtonRect(int buttonId);
	int getNumButtons();

	glm::vec2 getTextDims(int textId);
	void setTextPos(int textId, glm::vec2 pos);

	void setButtonOverlay(bool overlay, int buttonId);

private:

	SDL_Texture* m_texture;
	SDL_Rect m_srcRect, m_dstRect;

	glm::vec2 m_srcDimentions;
	glm::vec2 m_dstDimentions;

	std::vector<Button> m_buttons;
	std::vector<Text> m_texts;
};

