#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <glm.hpp>

class Text
{
public:
	Text(std::string font, int size, SDL_Color color, std::string message, glm::vec2 pos);
	Text(std::string font, int size, SDL_Color color, std::string message, glm::vec2 pos, SDL_Color backgroundColor);
	Text(std::string font, int size, SDL_Color color, std::string message, glm::vec2 pos, int wrapWidth);
	~Text();

	void update();
	void render();
	void setText(std::string text);

	glm::vec2 getDims();
	void setPos(glm::vec2 pos);

private:
	TTF_Font* m_font;
	SDL_Surface* m_surface;
	SDL_Texture* m_texture;
	SDL_Rect m_srcRect, m_dstRect;
	SDL_Color m_color;
	SDL_Color m_backgroundColor;
	int m_wrapWidth;
	bool m_background;

	glm::vec2 m_position;
	glm::vec2 m_dimentions;

};

