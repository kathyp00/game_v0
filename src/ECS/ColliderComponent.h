#pragma once
#include <string>
#include <SDL3/SDL.h>
using namespace std;

class ColliderComponent : public Component {

public:
    SDL_FRect collider;
    string tag;

    float height = 32.0f;
    float width = 32.0f;
    int scale = 1;

    TransformComponent* transform;
    ColliderComponent(string t) { tag = t; }


    void init() override {
        if (!entity->hasComponent<TransformComponent>()) {
            entity->addComponent<TransformComponent>();
        }
        transform = &entity->getComponent<TransformComponent>();
    }

    void update() override {
        collider.x = transform->position.x;
        collider.y = transform->position.y;
        collider.w = transform->width * transform->scale;
        collider.h = transform->height * transform->scale;
    }
};