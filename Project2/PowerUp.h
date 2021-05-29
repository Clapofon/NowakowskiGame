#pragma once

#include <glm.hpp>
#include <SDL.h>
#include <string>

class PowerUp
{
public:
	PowerUp(std::string tex, glm::vec2 pos, glm::vec2 srcDims, glm::vec2 dstDims, int lifetime);
	~PowerUp();

	bool update();
	void draw();

	glm::vec2 getPos();
	SDL_Rect getRect();

private:
	std::string m_texture;
	SDL_Rect m_srcRect, m_dstRect;

	glm::vec2 m_position;
	glm::vec2 m_srcDimentions;
	glm::vec2 m_dstDimentions;

	int m_lifetime;
	float m_counter;
};

