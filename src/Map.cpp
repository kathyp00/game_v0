#include "Map.h"
#include "TextureManager.h"
#include <algorithm>
#include "Game.h"
#include <fstream>
#include <string>
#include "ECS/ECS.h"
#include "ECS/TileComponent.h"
#include "ECS/ColliderComponent.h"
extern Manager manager;

Map::Map(string tID, int ms, int ts) : textID(tID), mapScale(ms), tileSize(ts) {
    scaledSize = ms * ts;
}

Map::~Map() {
}

void Map::loadMap(string path, int sizeX, int sizeY) {
    char c;
    fstream mapFile;
    mapFile.open(path);
    int srcX, srcY;
    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            mapFile.get(c);
            srcY = atoi(&c) * tileSize;
            mapFile.get(c);
            srcX = atoi(&c) * tileSize;
            addTile(srcX, srcY, x * scaledSize, y * scaledSize);
            mapFile.ignore();
        }
    }

    mapFile.ignore();
    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            mapFile.get(c);
            if (c == '1') {
                auto& tcol(manager.addEntity());
                tcol.addComponent<ColliderComponent>(x * scaledSize, y * scaledSize, scaledSize, "terrain");
                tcol.addGroup(Game::groupColliders);
            }
            mapFile.ignore();
        }
    }
    mapFile.close();
}

void Map::addTile(float srcX, float srcY, float xpos, float ypos) {
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, textID);
    tile.addGroup(Game::groupMap);
}