#pragma once

#include <glm.hpp>
#include <SDL.h>

#include <string>
#include <memory>

class Bullet
{
public:
	Bullet(glm::vec2 pos, glm::vec2 dir, float speed, float lifetime, bool rotate, double angle);
	~Bullet();

	bool update();
	void draw();
	SDL_Rect getRect();

private:
	float m_speed;
	int m_lifetime;
	double m_angle;
	double m_angleIncrease;

	bool m_rotate;

	glm::vec2 m_direction;
	glm::vec2 m_position;

	SDL_Rect m_srcRect, m_dstRect;
};

