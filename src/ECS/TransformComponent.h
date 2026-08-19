#pragma once
#include "Vector2D.h"

class TransformComponent : public Component {

public:
    Vector2D position;
    Vector2D velocity;
    int scale = 1;
    float width = 32.0f;
    float height = 32.0f;

    int speed = 3;

    TransformComponent() {
        position.x = 0.0f; 
        position.y = 0.0f; 
    }

    TransformComponent(int sc) {
        position.x = 0.0f; 
        position.y = 0.0f;
        scale = sc;
    }

    TransformComponent(float x, float y, float h, float w, int sc) {
        position.x = x; 
        position.y = y;
        height = h;
        width = w;
        scale = sc;
    }

    void init() override {
        velocity.x = 0.0f;
        velocity.y = 0.0f;
    }

    void update() override {
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }
};