#include "Bullet.h"

#include "ResourceManager.h"
#include "TextureManager.h"

Bullet::Bullet(glm::vec2 pos, glm::vec2 dir, float speed, float lifetime, bool rotate, double angle) :
    m_position(pos),
    m_direction(dir),
    m_speed(speed),
    m_lifetime(lifetime),
    m_rotate(rotate),
    m_angle(0),
    m_angleIncrease(angle)
{}

Bullet::~Bullet()
{
    //SDL_DestroyTexture(m_tex);
    //m_tex = nullptr;
}

bool Bullet::update()
{
    m_position.x += m_direction.x * m_speed;
    m_position.y += m_direction.y * m_speed;
    m_lifetime --;
    m_angle += m_angleIncrease;

    m_srcRect.h = 128;
    m_srcRect.w = 128;
    m_srcRect.x = 0;
    m_srcRect.y = 0;

    m_dstRect.x = m_position.x;
    m_dstRect.y = m_position.y;
    m_dstRect.w = 64;
    m_dstRect.h = 64;

    if (m_lifetime == 0)
    {
        return true;
    }
    else 
    {
        return false;
    }
}

void Bullet::draw()
{
    if (!m_rotate)
    {
        TextureManager::Draw(ResourceManager::getTexture("assets/czerwony_kafelek.png"), m_srcRect, m_dstRect);
    }
    else
    {
        SDL_Point* point = 0;
        TextureManager::Draw(ResourceManager::getTexture("assets/czerwony_kafelek.png"), m_srcRect, m_dstRect, m_angle, point, SDL_FLIP_NONE);
    }

    SDL_Point points[5] = {
        {m_dstRect.x, m_dstRect.y},
        {m_dstRect.x + m_dstRect.w, m_dstRect.y},
        {m_dstRect.x + m_dstRect.w, m_dstRect.y + m_dstRect.h},
        {m_dstRect.x, m_dstRect.y + m_dstRect.h},
        {m_dstRect.x, m_dstRect.y}
    };

    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLines(Game::renderer, points, 5);
}

SDL_Rect Bullet::getRect()
{
    return  m_dstRect;
}