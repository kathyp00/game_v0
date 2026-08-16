#pragma once

#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include <iostream>
#include <stdio.h>
using namespace std;

class Game {

public:
    Game();
    ~Game();

    void init(const char* title, int width, int height, bool fullscreen);
    void handle_events();
    void update();
    void render();
    void clean();
    bool running() { return isRunning; }

    static SDL_Renderer* renderer; 

private:
    bool isRunning;
    SDL_Window* window;
};