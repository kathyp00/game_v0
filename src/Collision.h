#pragma once
#include <SDL3/SDL.h>

class Collision {

public:
    static bool AABB(const SDL_FRect& recA, const SDL_FRect& recB);
};