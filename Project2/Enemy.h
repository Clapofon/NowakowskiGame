#pragma once

#include <SDL.h>
#include <vector>

#include "Bullet.h"
#include "TextureManager.h"

class Enemy
{
public:
	Enemy(std::string tex, glm::vec2 pos, glm::vec2 srcDims, glm::vec2 dstDims);
	~Enemy();

	void update();
	void draw();
	void sendBullet(std::vector<Bullet> &bullets, glm::vec2 targetPos, float speed, float lifetime,
					bool rotate, double angle, unsigned short int &counter, unsigned short int &num);
	glm::vec2 getDims();
	glm::vec2 getPos();
	void setPos(glm::vec2 pos);

private:

	glm::vec2 m_position;
	glm::vec2 m_srcDimentions;
	glm::vec2 m_dstDimentions;

	std::string m_texture;
	SDL_Rect m_srcRect, m_dstRect;
};

