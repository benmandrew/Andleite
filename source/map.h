#include <SDL2/SDL.h>
#include "sprite.h"

enum Tile {
    wall, open
};

class Map {
private:
    SDL_Surface* mapSurface;
    Tile grid[TILE_NUM_X][TILE_NUM_Y];

    static Sprite* wallSprite;
    static Sprite* openSprite;

    void init();
    void generateMap();
    void blitMap();
public:
    Map();
    ~Map();
};
