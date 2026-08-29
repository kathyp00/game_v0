#include "TextureManager.h"

SDL_Texture* TextureManager::loadTexture(const char* texture) {
    SDL_Surface* tmpSurface = IMG_Load(texture);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_NEAREST);
    SDL_DestroySurface(tmpSurface);
    return tex;
}

void TextureManager::draw(SDL_Texture* tex, SDL_FRect src, SDL_FRect dest, SDL_FlipMode flip) {
    SDL_RenderTextureRotated(Game::renderer, tex, &src, &dest, 0.0, NULL, flip);
}