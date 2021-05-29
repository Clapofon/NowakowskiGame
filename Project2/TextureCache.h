#pragma once

#include <map>
#include <string>

#include <SDL.h>

class TextureCache
{
public:
    TextureCache();
    ~TextureCache();

    SDL_Texture* getTexture(std::string texturePath);

private:

    std::map<std::string, SDL_Texture*> m_textureMap;
};

