#pragma once
#include <SDL3/SDL.h>
#include "Vector2D.h"
#include "AssetManager.h"

class TileComponent : public Component {

public :
    SDL_Texture* texture;
    SDL_FRect srcRect, destRect;
    Vector2D position;

    TileComponent() = default;
    ~TileComponent() { SDL_DestroyTexture(texture); }
    TileComponent(float srcX, float srcY, float xpos, float ypos, int tsize, int tscale, string id) {
        texture = Game::assets->getTexture(id);
    
        position.x = xpos;
        position.y = ypos;
    
        srcRect.x = srcX;
        srcRect.y = srcY;
        srcRect.w = srcRect.h = tsize;
    
        destRect.x = xpos;
        destRect.y = ypos;
        destRect.w = destRect.h = tsize * tscale;
    }

    void update() override {
        destRect.x = position.x - Game::camera.x;
        destRect.y = position.y - Game::camera.y;
    }

    void draw() override {
        TextureManager::draw(texture, srcRect, destRect, SDL_FLIP_NONE);
    }
};