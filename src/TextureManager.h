#pragma once
#include "Game.h"

class TextureManager {

public :
    static SDL_Texture* loadTexture(const char* fileName);
    static void draw(SDL_Texture* tex, SDL_FRect src, SDL_FRect dest, SDL_FlipMode flip);

};