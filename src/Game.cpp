#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"


Map* gmap;
Manager manager;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
SDL_FRect Game::camera = {0, 0, 800, 600};

vector<ColliderComponent*> Game::colliders;

bool Game::isRunning = false;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

const char* mapfile = "asset/merge.png";

enum groupLabels : size_t {
    groupMap,
    groupPlayers,
    groupEnemies,
    groupColliders
};


auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));

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

    gmap = new Map();
    Map::loadMap("asset/level0.map", 16, 16);
    
    player.addComponent<TransformComponent>(4);
    player.addComponent<SpriteComponent>("asset/player_anims.png", true);
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayers);

}

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
    manager.refresh();
    manager.update();

    camera.x = player.getComponent<TransformComponent>().position.x - 400;
    camera.y = player.getComponent<TransformComponent>().position.y - 300;

    camera.x = (camera.x < 0) ? 0 : ((camera.x > camera.w) ? camera.w : camera.x);
    camera.y = (camera.y < 0) ? 0 : ((camera.y > camera.h) ? camera.h : camera.y);
}

void Game::render() {
    SDL_RenderClear(renderer);
    for (auto& t : tiles) {
        t->draw();
    }
    for (auto& p : players) {
        p->draw();
    }
    for (auto& e : enemies) {
        e->draw();
    }
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout << "game cleaned" << endl;
}

void Game::addTile(float srcX, float srcY, float xpos, float ypos) {
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, mapfile);
    tile.addGroup(groupMap);
}
