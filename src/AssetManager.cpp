#include "AssetManager.h"
#include "ECS/TransformComponent.h"
#include "ECS/SpriteComponent.h"
#include "ECS/ProjectileComponent.h"
#include "ECS/ColliderComponent.h"

AssetManager::AssetManager(Manager* man) : manager(man) {}

AssetManager::~AssetManager() {}

void AssetManager::createProjectile(Vector2D pos, Vector2D val, int range, int speed, string id) {
    auto& projectile(manager->addEntity());
    projectile.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, 1);
    projectile.addComponent<SpriteComponent>(id, false);
    projectile.addComponent<ProjectileComponent>(range, speed, val);
    projectile.addComponent<ColliderComponent>("projectile");
    projectile.addGroup(Game::groupProjectiles);

}

void AssetManager::addTexture(string id, const char* path) {
    texture.emplace(id, TextureManager::loadTexture(path));
}

SDL_Texture* AssetManager::getTexture(string id) {
    return texture[id];
}


