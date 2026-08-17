#pragma once
#include <SDL3/SDL.h>

class SpriteComponent : public Component {

private:
    TransformComponent* transform;
    SDL_Texture* texture;
    SDL_FRect srcRect, destRect;

public:
    SpriteComponent() = default;
    SpriteComponent(const char* path) {
        setTex(path);
    }

    void setTex(const char* path) {
        texture = TextureManager::LoadTexture(path); 
    }

    void init() override {
        transform = &entity->getComponent<TransformComponent>();
        srcRect.x = srcRect.y = 0.0f;
        srcRect.w = srcRect.h = 32.0f;
        destRect.w = destRect.h = 64.0f;
    }

    void update() override {
        destRect.x = transform->position.x;
        destRect.y = transform->position.y;
    }

    void draw() override {
        TextureManager::Draw(texture, srcRect, destRect);
    }
};