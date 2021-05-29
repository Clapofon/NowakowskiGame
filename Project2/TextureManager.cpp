#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture)
{
    SDL_Surface* tmpSurface = IMG_Load(texture);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    printf("loading tex\n");

    return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dst)
{
    SDL_RenderCopy(Game::renderer, tex, &src, &dst);
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dst, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(Game::renderer, tex, &src, &dst, angle, center, flip);
}

