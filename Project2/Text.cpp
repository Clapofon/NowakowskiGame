#include "Text.h"
#include "Game.h"
#include "TextureManager.h"

Text::Text(std::string font, int size, SDL_Color color, std::string message, glm::vec2 pos) :
	m_position(pos),
	m_color(color),
	m_background(false)
{
	m_font = TTF_OpenFont(font.c_str(), size);
	if (m_font == NULL)
	{
		std::cerr << "Error : " << TTF_GetError() << std::endl;
	}

	m_surface = TTF_RenderText_Blended(m_font, message.c_str(), m_color);

	m_texture = SDL_CreateTextureFromSurface(Game::renderer, m_surface);

	m_dimentions.x = m_surface->w;
	m_dimentions.y = m_surface->h;

	SDL_FreeSurface(m_surface);
}

Text::Text(std::string font, int size, SDL_Color color, std::string message, glm::vec2 pos, SDL_Color backgroundColor) :
	m_position(pos),
	m_color(color),
	m_backgroundColor(backgroundColor),
	m_background(true)
{
	m_font = TTF_OpenFont(font.c_str(), size);
	if (m_font == NULL)
	{
		std::cerr << "Error : " << TTF_GetError() << std::endl;
	}

	m_surface = TTF_RenderText_Blended(m_font, message.c_str(), m_color);

	m_texture = SDL_CreateTextureFromSurface(Game::renderer, m_surface);

	m_dimentions.x = m_surface->w;
	m_dimentions.y = m_surface->h;

	SDL_FreeSurface(m_surface);
}

Text::Text(std::string font, int size, SDL_Color color, std::string message, glm::vec2 pos, int wrapWidth) :
	m_position(pos),
	m_color(color),
	m_wrapWidth(wrapWidth),
	m_background(false)
{
	m_font = TTF_OpenFont(font.c_str(), size);
	if (m_font == NULL)
	{
		std::cerr << "Error : " << TTF_GetError() << std::endl;
	}

	m_surface = TTF_RenderText_Blended(m_font, message.c_str(), m_color);

	m_texture = SDL_CreateTextureFromSurface(Game::renderer, m_surface);

	m_dimentions.x = m_surface->w;
	m_dimentions.y = m_surface->h;

	SDL_FreeSurface(m_surface);
}

Text::~Text()
{}

void Text::update()
{
	m_srcRect.x = 0;
	m_srcRect.y = 0;
	m_srcRect.w = m_dimentions.x;
	m_srcRect.h = m_dimentions.y;

	m_dstRect.x = m_position.x;
	m_dstRect.y = m_position.y;
	m_dstRect.w = m_dimentions.x;
	m_dstRect.h = m_dimentions.y;
}

void Text::render()
{
	if (m_background)
	{
		SDL_SetRenderDrawBlendMode(Game::renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(Game::renderer, m_backgroundColor.r, m_backgroundColor.g, m_backgroundColor.b, m_backgroundColor.a);
		SDL_RenderFillRect(Game::renderer, &m_dstRect);
	}

	TextureManager::Draw(m_texture, m_srcRect, m_dstRect);
}

void Text::setText(std::string text)
{
	m_surface = TTF_RenderText_Blended(m_font, text.c_str(), m_color);

	m_texture = SDL_CreateTextureFromSurface(Game::renderer, m_surface);

	m_dimentions.x = m_surface->w;
	m_dimentions.y = m_surface->h;

	SDL_FreeSurface(m_surface);
}

glm::vec2 Text::getDims()
{
	return m_dimentions;
}

void Text::setPos(glm::vec2 pos)
{
	m_position = pos;
}