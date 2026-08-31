#pragma once
#include "Game.h"
#include "ECS.h"

class KeyboardController : public Component {

public :
    TransformComponent *transform;
    SpriteComponent* sprite;

    void init() override {
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
    }

    void update() override {
        if (Game::event.type == SDL_EVENT_KEY_DOWN) {
            switch (Game::event.key.key) {
                case SDLK_W :
                    transform->velocity.y = -1;
                    sprite->play("walk");
                    break;
                case SDLK_A :
                    transform->velocity.x = -1;
                    sprite->play("walk");
                    sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
                    break;
                case SDLK_D :
                    transform->velocity.x = 1;
                    sprite->play("walk");
                    break;
                case SDLK_S :
                    transform->velocity.y = 1;
                    sprite->play("walk");
                    break;
                default : 
                    break;  
            }
        }
        if (Game::event.type == SDL_EVENT_KEY_UP) {
            switch (Game::event.key.key) {
                case SDLK_W :
                    transform->velocity.y = 0;
                    sprite->play("idle");
                    break;
                case SDLK_A :
                    transform->velocity.x = 0;
                    sprite->play("idle");
                    sprite->spriteFlip = SDL_FLIP_NONE;
                    break;
                case SDLK_D :
                    transform->velocity.x = 0;
                    sprite->play("idle");
                    break;
                case SDLK_S :
                    transform->velocity.y = 0;
                    sprite->play("idle");
                    break;
                case SDLK_ESCAPE :
                    Game::isRunning = false;
                default : 
                    break;  
            }
        }
    }
};
