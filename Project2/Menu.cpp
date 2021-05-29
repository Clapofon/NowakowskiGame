#include "Menu.h"
#include "TextureManager.h"

Menu::Menu(std::string tex, glm::vec2 srcDims, glm::vec2 dstDims) :
	m_texture(TextureManager::LoadTexture(tex.c_str())),
	m_srcDimentions(srcDims),
	m_dstDimentions(dstDims)
{}

Menu::~Menu()
{}

void Menu::update()
{
	m_srcRect.x = 0;
	m_srcRect.y = 0;
	m_srcRect.w = m_srcDimentions.x;
	m_srcRect.h = m_srcDimentions.y;

	m_dstRect.x = 0;
	m_dstRect.y = 0;
	m_dstRect.w = m_dstDimentions.x;
	m_dstRect.h = m_dstDimentions.y;

	for (int i = 0; i < m_buttons.size(); i ++)
	{
		m_buttons[i].update();
	}

	for (int i = 0; i < m_texts.size(); i ++)
	{
		m_texts[i].update();
	}
}

void Menu::draw()
{
	TextureManager::Draw(m_texture, m_srcRect, m_dstRect);

	for (int i = 0; i < m_buttons.size(); i ++)
	{
		m_buttons[i].draw();
	}

	for (int i = 0; i < m_texts.size(); i ++)
	{
		m_texts[i].render();
	}
}

void Menu::addButton(std::string font, int size, SDL_Color color, std::string message, glm::vec2 pos, glm::vec2 dims, SDL_Color backgroundColor)
{
	m_buttons.emplace_back(font, size, color, message, pos, dims, backgroundColor);
}

void Menu::addButton(std::string font, int size, SDL_Color color, std::string message, glm::vec2 pos, glm::vec2 dims, SDL_Color backgroundColor, bool overlay)
{
	m_buttons.emplace_back(font, size, color, message, pos, dims, backgroundColor, overlay);
}

void Menu::addText(std::string font, int size, SDL_Color color, std::string message, glm::vec2 pos)
{
	m_texts.emplace_back(font, size, color, message, pos);
}

void Menu::addText(std::string font, int size, SDL_Color color, std::string message, glm::vec2 pos, int wrapWidth)
{
	m_texts.emplace_back(font, size, color, message, pos, wrapWidth);
}

SDL_Rect Menu::getButtonRect(int buttonId)
{
	return m_buttons[buttonId].getRect(buttonId);
}

glm::vec2 Menu::getTextDims(int textId)
{
	return m_texts[textId].getDims();
}

void Menu::setTextPos(int textId, glm::vec2 pos)
{
	m_texts[textId].setPos(pos);
}

void Menu::setButtonOverlay(bool overlay, int buttonId)
{
	m_buttons[buttonId].setOverlay(overlay);
}

int Menu::getNumButtons()
{
	return m_buttons.size();
}