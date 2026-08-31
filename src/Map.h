#include "Game.h"
using namespace std;

class Map {

public :
    Map(string tID, int ms, int ts);
    ~Map();

    void loadMap(string path, int sizeX, int sizeY);
    void addTile(float srcX, float srcY, float xpos, float ypos);

private :
    string textID;
    int mapScale;
    int tileSize;
    float scaledSize;
};
