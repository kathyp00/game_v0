#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/TransformComponent.h"
#include "ECS/SpriteComponent.h"
#include "ECS/KeyboardController.h"
#include "ECS/ColliderComponent.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"


Map* gmap;
Manager manager;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
SDL_FRect Game::camera = {0, 0, 800, 640};

AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;
auto& player(manager.addEntity());

Game::Game() {}

Game::~Game() {}

void Game::init(const char* title, int width, int height, bool fullscreen) {
    int flag = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;

    if (SDL_Init(SDL_INIT_VIDEO)) {
        cout << "init" << endl;

        if (!SDL_CreateWindowAndRenderer(title, width, height, flag, &window, &renderer)) {
            cout << "window and renderer creation failed" << endl;
        }

        // use to match monitor's refresh rate
        SDL_SetRenderVSync(renderer, 1); // 1 = Enable VSync, 0 = Disable

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        isRunning = true;
    } else {
        isRunning = false;
    }

    assets->addTexture("terrain", "asset/terrain_ss.png");
    assets->addTexture("player", "asset/player_anims.png");
    assets->addTexture("projectile", "asset/proj.png");

    gmap = new Map("terrain", 3, 32);
    gmap->loadMap("asset/map.map", 25, 20);
    
    player.addComponent<TransformComponent>(800.0f, 640.0f, 32 , 32, 4);
    player.addComponent<SpriteComponent>("player", true);
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayers);

    assets->createProjectile(Vector2D(600, 600), Vector2D(2, 0), 200, 2, "projectile");
    assets->createProjectile(Vector2D(600, 620), Vector2D(2, 0), 200, 2, "projectile");
    assets->createProjectile(Vector2D(400, 600), Vector2D(2, 1), 200, 2, "projectile");
    assets->createProjectile(Vector2D(600, 600), Vector2D(2, -1), 200, 2, "projectile");

}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));

void Game::handleEvents() {
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_EVENT_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}

void Game::update() {
    SDL_FRect playerCol = player.getComponent<ColliderComponent>().collider;
    Vector2D playerPos = player.getComponent<TransformComponent>().position;

    manager.refresh();
    manager.update();

    for (auto& c : colliders) {
        SDL_FRect cCol = c->getComponent<ColliderComponent>().collider;
        if (Collision::AABB(cCol, playerCol)) {
            player.getComponent<TransformComponent>().position = playerPos;
        }
    }

    for(auto& p : projectiles) {
        if (Collision::AABB(player.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider)) {
            p->destroy();
        }
    }

    camera.x = player.getComponent<TransformComponent>().position.x - 400;
    camera.y = player.getComponent<TransformComponent>().position.y - 320;

    camera.x = (camera.x < 0) ? 0 : ((camera.x > camera.w) ? camera.w : camera.x);
    camera.y = (camera.y < 0) ? 0 : ((camera.y > camera.h) ? camera.h : camera.y);
}

void Game::render() {
    SDL_RenderClear(renderer);
    for (auto& t : tiles) {
        t->draw();
    }
    for (auto& c : colliders) {
        c->draw();
    }
    for (auto& p : players) {
        p->draw();
    }
    for (auto& p : projectiles) {
        p->draw();
    }
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout << "game cleaned" << endl;
}
