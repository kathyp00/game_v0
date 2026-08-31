#pragma once

#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;

class AssetManager;
class ColliderComponent;

class Game {

public :
    Game();
    ~Game();

    void init(const char* title, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool running() { return isRunning; }

    static SDL_Renderer* renderer;
    static SDL_Event event;
    static bool isRunning;
    static SDL_FRect camera;
    static AssetManager* assets;

    enum groupLabels : size_t {
        groupMap,
        groupPlayers,
        groupColliders,
        groupProjectiles
    };

private :
    SDL_Window* window;
};