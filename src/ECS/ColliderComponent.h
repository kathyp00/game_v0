#pragma once
#include <string>
#include <SDL3/SDL.h>
#include "ECS.h"
#include "TransformComponent.h"
#include "Game.h"
#include "TextureManager.h"
using namespace std;

class ColliderComponent : public Component {

public :
    SDL_FRect collider;
    string tag;

    SDL_Texture* tex;
    SDL_FRect srcR, destR;

    float height = 32.0f;
    float width = 32.0f;
    int scale = 1;

    TransformComponent* transform;
    ColliderComponent(string t) { tag = t; }

    ColliderComponent(float xpos, float ypos, float size, const char* t) {
        tag = t;
        collider.x = xpos;
        collider.y = ypos;
        collider.h = collider.w = size;
    }

    void init() override {
        if (!entity->hasComponent<TransformComponent>()) {
            entity->addComponent<TransformComponent>();
        }
        transform = &entity->getComponent<TransformComponent>();
        tex = TextureManager::loadTexture("asset/coltex.png");
        srcR = {0.0f, 0.0f, height, width};
        destR = { collider.x, collider.y, collider.w, collider.h};
        
    }

    void update() override {
        if (tag != "terrain") {
            collider.x = transform->position.x;
            collider.y = transform->position.y;
            collider.w = transform->width * transform->scale;
            collider.h = transform->height * transform->scale;
        }
        destR.x = collider.x - Game::camera.x;
        destR.y = collider.y - Game::camera.y;
    }

    void draw() override {
        TextureManager::draw(tex, srcR, destR, SDL_FLIP_NONE);
    }
};