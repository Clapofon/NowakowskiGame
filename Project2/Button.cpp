#include "Button.h"
#include "TextureManager.h"

Button::Button(std::string font, int size, SDL_Color color, std::string message, glm::vec2 pos, glm::vec2 dims, SDL_Color backgroundColor) :
	m_position(pos),
	m_dimentions(dims),
	m_isOverlay(false),
	m_color(backgroundColor)
{
	m_text = new Text(font.c_str(), size, color, message.c_str(), pos);

	glm::vec2 textPos;
	textPos.x = pos.x + (dims.x / 2) - m_text->getDims().x / 2;
	textPos.y = pos.y + (dims.y / 2) - m_text->getDims().y / 2;

	m_text->setPos(textPos);
}

Button::Button(std::string font, int size, SDL_Color color, std::string message, glm::vec2 pos, glm::vec2 dims, SDL_Color backgroundColor, bool overlay) :
	m_position(pos),
	m_dimentions(dims),
	m_color(backgroundColor),
	m_isOverlay(overlay),
	m_counter(0.0f)
{
	m_text = new Text(font.c_str(), size, color, message.c_str(), pos);

	glm::vec2 textPos;
	textPos.x = pos.x + (dims.x / 2) - m_text->getDims().x / 2;
	textPos.y = pos.y + (dims.y / 2) - m_text->getDims().y / 2;

	m_text->setPos(textPos);
}

Button::~Button()
{
	
}

void Button::update()
{
	m_dstRect.x = m_position.x;
	m_dstRect.y = m_position.y;
	m_dstRect.w = m_dimentions.x;
	m_dstRect.h = m_dimentions.y;

	m_text->update();
}

void Button::draw()
{
	SDL_SetRenderDrawBlendMode(Game::renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(Game::renderer, m_color.r, m_color.g, m_color.b, m_color.a);
	SDL_RenderFillRect(Game::renderer, &m_dstRect);

	if (m_isOverlay)
	{
		m_counter += 0.15;

		float val = glm::cos(m_counter * 0.2);
		//std::cout << val << std::endl;
		val *= 255;
		if (val < 0)
		{
			val *= -1;
		}

		val = glm::clamp(val, 120.0f, 255.0f);

		SDL_Point pointsFirst[5] = {
			{m_dstRect.x, m_dstRect.y},
			{m_dstRect.x + m_dstRect.w, m_dstRect.y},
			{m_dstRect.x + m_dstRect.w, m_dstRect.y + m_dstRect.h},
			{m_dstRect.x, m_dstRect.y + m_dstRect.h},
			{m_dstRect.x, m_dstRect.y}
		};

		SDL_Point pointsSecond[13] = {
			{m_dstRect.x + 7, m_dstRect.y + 2},
			{(m_dstRect.x + m_dstRect.w) - 7, m_dstRect.y + 2},
			{(m_dstRect.x + m_dstRect.w) - 7, m_dstRect.y + 7},
			{(m_dstRect.x + m_dstRect.w) - 2, m_dstRect.y + 7},
			{(m_dstRect.x + m_dstRect.w) - 2, (m_dstRect.y + m_dstRect.h) - 7},
			{(m_dstRect.x + m_dstRect.w) - 7, (m_dstRect.y + m_dstRect.h) - 7},
			{(m_dstRect.x + m_dstRect.w) - 7, (m_dstRect.y + m_dstRect.h) - 2},
			{m_dstRect.x + 7, (m_dstRect.y + m_dstRect.h) - 2},
			{m_dstRect.x + 7, (m_dstRect.y + m_dstRect.h) - 7},
			{m_dstRect.x + 2, (m_dstRect.y + m_dstRect.h) - 7},
			{m_dstRect.x + 2, m_dstRect.y + 7},
			{m_dstRect.x + 7, m_dstRect.y + 7},
			{m_dstRect.x + 7, m_dstRect.y + 2}
		};

		SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, val);
		SDL_RenderDrawLines(Game::renderer, pointsFirst, 5);
		SDL_RenderDrawLines(Game::renderer, pointsSecond, 13);
	}

	m_text->render();
}

SDL_Rect Button::getRect(int buttonId)
{
	return m_dstRect;
}

void Button::setOverlay(bool overlay)
{
	m_isOverlay = overlay;
}
