#include "TextureCache.h"
#include "TextureManager.h"

#include <iostream>


TextureCache::TextureCache()
{}

TextureCache::~TextureCache()
{}

SDL_Texture* TextureCache::getTexture(std::string texturePath)
{
    auto mit = m_textureMap.find(texturePath);

    if (mit == m_textureMap.end())
    {
        SDL_Texture* newTexture = TextureManager::LoadTexture(texturePath.c_str());

        m_textureMap.insert(make_pair(texturePath, newTexture));

        return newTexture;
    }

    return mit->second;
}

