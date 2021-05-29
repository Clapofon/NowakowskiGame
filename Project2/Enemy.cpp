#include "Enemy.h"
#include "ResourceManager.h"

#include <ctime>

Enemy::Enemy(std::string tex, glm::vec2 pos, glm::vec2 srcDims, glm::vec2 dstDims) :
    m_position(pos),
    m_texture(tex),
    m_srcDimentions(srcDims),
    m_dstDimentions(dstDims)
{}

Enemy::~Enemy()
{}

void Enemy::update()
{
    m_srcRect.h = m_srcDimentions.y;
    m_srcRect.w = m_srcDimentions.x;
    m_srcRect.x = 0;
    m_srcRect.y = 0;

    m_dstRect.x = m_position.x;
    m_dstRect.y = m_position.y;
    m_dstRect.w = m_dstDimentions.x;
    m_dstRect.h = m_dstDimentions.y;
}

void Enemy::draw()
{
    TextureManager::Draw(ResourceManager::getTexture(m_texture) , m_srcRect, m_dstRect);

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

void Enemy::sendBullet(std::vector<Bullet>& bullets, glm::vec2 targetPos, float speed, float lifetime,
                        bool rotate, double angle, unsigned short int &counter, unsigned short int &num)
{
    if (counter % num == 0)
    {
        counter = 0;
        glm::vec2 pos;
        pos.x = m_position.x + (m_dstDimentions.x / 2);
        pos.y = m_position.y + (m_dstDimentions.y / 2);

        glm::vec2 dir = targetPos - pos;
        dir = glm::normalize(dir);

        bullets.emplace_back(pos, dir, speed, lifetime, rotate, angle);
    }
}

glm::vec2 Enemy::getDims()
{
    return m_dstDimentions;
}

glm::vec2 Enemy::getPos()
{
    return m_position;
}
void Enemy::setPos(glm::vec2 pos)
{
    m_position = pos;
}