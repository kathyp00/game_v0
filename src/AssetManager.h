#pragma once

#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS/ECS.h"
using namespace std;

class AssetManager {

public :
    AssetManager(Manager* man);
    ~AssetManager();

    // gameobjects
    void createProjectile(Vector2D pos, Vector2D val, int range, int speed, string id);

    // texture management
    void addTexture(string id, const char* path);
    SDL_Texture* getTexture(string id);
    

private :
    Manager* manager;
    map<string, SDL_Texture*> texture;

};