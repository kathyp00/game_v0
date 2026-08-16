#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"

GameObject* player;
GameObject* enemy;
Map* map;


SDL_Renderer* Game::renderer = nullptr;


Game::Game() {

}

Game::~Game() {

}

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

    player = new GameObject("asset/player.png", 0, 0);
    enemy = new GameObject("asset/enemy.png", 50, 50);
    map = new Map();
}

void Game::handle_events() {
    SDL_Event event;
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
    player->Update();
    enemy->Update();
}

void Game::render() {
    SDL_RenderClear(renderer);
    map->DrawMap();
    player->Render();
    enemy->Render();
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout << "game cleaned" << endl;
}
