#pragma once
#include <SDL3/SDL.h>

class TileComponent : public Component {

public :
    SDL_Texture* texture;
    SDL_FRect srcRect, destRect;
    Vector2D position;

    TileComponent() = default;
    ~TileComponent() { SDL_DestroyTexture(texture); }
    TileComponent(float srcX, float srcY, float xpos, float ypos, const char* path) {
        texture = TextureManager::loadTexture(path);
    
        position.x = xpos;
        position.y = ypos;
    
        srcRect.x = srcX;
        srcRect.y = srcY;
        srcRect.w = srcRect.h = 32;
    
        destRect.x = xpos;
        destRect.y = ypos;
        destRect.w = destRect.h = 64;
    }

    void update() override {
        destRect.x = position.x - Game::camera.x;
        destRect.y = position.y - Game::camera.y;
    }

    void draw() override {
        TextureManager::draw(texture, srcRect, destRect, SDL_FLIP_NONE);
    }
};