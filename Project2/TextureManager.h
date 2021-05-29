#ifndef TEXTUREMANAGER_H_INCLUDED
#define TEXTUREMANAGER_H_INCLUDED

#include "Game.h"

class TextureManager
{
public:
    static SDL_Texture* LoadTexture(const char* texture);
    static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dst);
    static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dst, double angle, SDL_Point* center, SDL_RendererFlip flip);
};
#endif // TEXTUREMANAGER_H_INCLUDED
