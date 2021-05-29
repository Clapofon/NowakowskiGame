#ifndef GAMEOBJECT_HPP_INCLUDED
#define GAMEOBJECT_HPP_INCLUDED

#include "Game.h"

#include <glm.hpp>

class GameObject
{
public:

    GameObject(std::string texturesheet, glm::vec2 pos, glm::vec2 srcDimentions, glm::vec2 dstDimentions);
    ~GameObject();

    void update();
    void render();

    glm::vec2 getpos();
    glm::vec2 getDims();
    SDL_Rect getRect();
    void setpos(glm::vec2 amt);

    short int getHealth();
    void setHealth(short int health);

private:
    glm::vec2 m_position;
    glm::vec2 m_srcDimentions;
    glm::vec2 m_dstDimentions;

    short int m_health;

    SDL_Texture* m_objTexture;
    SDL_Rect m_srcRect, m_destRect;
};

#endif // GAMEOBJECT_HPP_INCLUDED
