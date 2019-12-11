#pragma once

#include <random>
#include <vector>
#include <time.h>
#include <SDL2/SDL.h>
#include "sprite.h"

enum Tile {
    wall, open
};

struct Room {
    int x0, y0, x1, y1;

    bool collidesWith(Room other);
};

class Map {
private:
    SDL_Rect mapPosRect;
    SDL_Surface* mapSurface;
    Tile grid[TILE_NUM_X][TILE_NUM_Y];
    std::vector<Room> rooms;

    static Sprite* wallSprite;
    static Sprite* openSprite;

    void generateMap();
    void generateRooms();
    void generateRoom(
        int x0, int y0, int x1, int y1);
    void blitMap();
public:
    Map();
    ~Map();

    void init();
    SDL_Rect* getRect();
    SDL_Surface* getSurface();
};
