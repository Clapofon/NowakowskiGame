#pragma once

#include "TextureCache.h"


class ResourceManager
{
public:
    static SDL_Texture* getTexture(std::string texturePath);

private:
    static TextureCache m_textureCache;
};
