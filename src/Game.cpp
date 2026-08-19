#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"


Map* map;
Manager manager;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
auto& player(manager.addEntity());
auto& wall(manager.addEntity());

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

    map = new Map();
    player.addComponent<TransformComponent>(2);
    player.addComponent<SpriteComponent>("asset/player.png");
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");

    wall.addComponent<TransformComponent>(300.0f, 300.0f, 300.0f, 20.0f, 1);
    wall.addComponent<SpriteComponent>("asset/dirt.png");
    wall.addComponent<ColliderComponent>("wall");
}

void Game::handle_events() {
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
    manager.refresh();
    manager.update();

    if (Collision::AABB(player.getComponent<ColliderComponent>().collider, wall.getComponent<ColliderComponent>().collider)) {
        player.getComponent<TransformComponent>().scale = 1;
        cout << "wall hit" << endl;
    }
}

void Game::render() {
    SDL_RenderClear(renderer);
    map->DrawMap();
    manager.draw();
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout << "game cleaned" << endl;
}
