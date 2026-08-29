#pragma once

#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;

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

    static void addTile(float srcX, float srcY, float xpos, float ypos);
    static SDL_Renderer* renderer;
    static SDL_Event event;
    static vector<ColliderComponent*> colliders;
private :
    bool isRunning;
    SDL_Window* window;
};