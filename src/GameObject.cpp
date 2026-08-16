#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* texturesheet, float x, float y) {
    objTexture = TextureManager::LoadTexture(texturesheet);

    xpos = x;
    ypos = y;
}

void GameObject::Update() {

    xpos++;
    ypos++;
    srcRect.h = 32.0f;
    srcRect.w = 32.0f;
    srcRect.x = 0.0f;
    srcRect.y = 0.0f;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w * 2;
    destRect.h = srcRect.h * 2;
}

void GameObject::Render() {
    SDL_RenderTexture(Game::renderer, objTexture, &srcRect, &destRect);

}

