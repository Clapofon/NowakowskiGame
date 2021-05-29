#include "PowerUp.h"
#include "TextureManager.h"
#include "ResourceManager.h"


PowerUp::PowerUp(std::string tex, glm::vec2 pos, glm::vec2 srcDims, glm::vec2 dstDims, int lifetime) :
	m_position(pos),
	m_dstDimentions(dstDims),
	m_srcDimentions(srcDims),
	m_lifetime(lifetime),
	m_texture(tex)
{}

PowerUp::~PowerUp()
{}

bool PowerUp::update()
{
    m_lifetime --;
    m_counter += 0.1;

    if (m_lifetime <= 0)
    {
        return true;
    }

    m_srcRect.h = m_srcDimentions.y;
    m_srcRect.w = m_srcDimentions.x;
    m_srcRect.x = 0;
    m_srcRect.y = 0;

    m_dstRect.x = m_position.x;
    m_dstRect.y = m_position.y;
    m_dstRect.w = m_dstDimentions.x;
    m_dstRect.h = m_dstDimentions.y;

    return false;
}

void PowerUp::draw()
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

glm::vec2 PowerUp::getPos()
{
    return m_position;
}

SDL_Rect PowerUp::getRect()
{
    return m_dstRect;
}