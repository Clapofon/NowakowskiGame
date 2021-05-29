#include "GameObject.hpp"
#include "TextureManager.h"
#include "ResourceManager.h"

GameObject::GameObject(std::string texturesheet, glm::vec2 pos, glm::vec2 srcDimentions, glm::vec2 dstDimentions)
{
    m_objTexture = ResourceManager::getTexture(texturesheet);

    m_position = pos;

    m_srcDimentions = srcDimentions;
    m_dstDimentions = dstDimentions;

    m_health = 100;
}

GameObject::~GameObject() 
{}

void GameObject::update()
{
    m_srcRect.h = m_srcDimentions.y;
    m_srcRect.w = m_srcDimentions.x;
    m_srcRect.x = 0;
    m_srcRect.y = 0;

    m_destRect.x = m_position.x;
    m_destRect.y = m_position.y;
    m_destRect.w = m_dstDimentions.x;
    m_destRect.h = m_dstDimentions.y;
}

void GameObject::render()
{
    TextureManager::Draw(m_objTexture, m_srcRect, m_destRect);
}

glm::vec2 GameObject::getpos()
{
    return m_position;
}

glm::vec2 GameObject::getDims()
{
    return m_dstDimentions;
}

SDL_Rect GameObject::getRect()
{
    return m_destRect;
}

void GameObject::setpos(glm::vec2 amt)
{
    m_position = amt;
}

short int GameObject::getHealth()
{
    return m_health;
}

void GameObject::setHealth(short int health)
{
    m_health = health;
}
