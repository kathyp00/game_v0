#pragma once
#include <SDL3/SDL.h>
#include <TextureManager.h>
#include "Animation.h"
#include "AssetManager.h"
#include <map>
using namespace std;

class SpriteComponent : public Component {

private :
    TransformComponent* transform;
    SDL_Texture* texture;
    SDL_FRect srcRect, destRect;

    bool animated = false;
    int frames = 0;
    int speed = 100;

public :
    int animIndex = 0;
    std::map<const char*, Animation> animations;
    SDL_FlipMode spriteFlip = SDL_FLIP_NONE;

    SpriteComponent() = default;
    SpriteComponent(const char* path) {
        setTex(path);
    }
    SpriteComponent(string id, bool isAnimated) {
        animated = isAnimated;
        Animation idle = Animation(0, 3, 100);
        Animation walk = Animation(1, 8, 100);
        animations.emplace("idle", idle);
        animations.emplace("walk", walk);
        play("idle");
        setTex(id);
    }

    ~SpriteComponent() {
    }

    void setTex(string id) {
        texture = Game::assets->getTexture(id);
    }

    void init() override {
        transform = &entity->getComponent<TransformComponent>();
        srcRect.x = 0.0f;
        srcRect.y = 0.0f;
        srcRect.w = transform->width;
        srcRect.h = transform->height;
    }

    void update() override {
        if (animated) {
            srcRect.x = srcRect.w * ((SDL_GetTicks() / speed) % frames);
        }
        srcRect.y = animIndex * transform->height;
        destRect.x = transform->position.x - Game::camera.x;
        destRect.y = transform->position.y - Game::camera.y;
        destRect.w = transform->width * transform->scale; 
        destRect.h = transform->height * transform->scale;
    }

    void draw() override {
        TextureManager::draw(texture, srcRect, destRect, spriteFlip);
    }

    void play(const char* animName) {
        frames = animations[animName].frames;
        animIndex = animations[animName].index;
        speed = animations[animName].speed;
    }
};