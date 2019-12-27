#pragma once

#include <random>
#include <vector>
#include <time.h>
#include <SDL2/SDL.h>
#include "sprite.h"
#include "vec2.h"
#include "region.h"

enum Direction {
    north, east, south, west
};

class Map {
private:
    SDL_Rect mapPosRect;
    SDL_Surface* mapSurface;
    Tile grid[TILE_NUM_X][TILE_NUM_Y];
    std::vector<Region> rooms;

    static Sprite* wallSprite;
    static Sprite* openSprite;

    void generateMap();
    void generateRooms();
    void generateRoom(
        int x0, int y0, int x1, int y1);
    void generateCorridor(Vec2 pos);
    bool extendCorridor(Vec2* currentPos);
    void connectRegions();

    bool adjacentToOpen(
        const Vec2 pos) const;
    bool adjacentToOpenInDirection(
        const Vec2 pos, const Vec2 offset,
        const Direction dir) const;

    void blitMap();
public:
    Map();
    ~Map();

    void init();
    Tile getTile(const Vec2 pos) const;
    SDL_Rect* getRect();
    SDL_Surface* getSurface() const;
};
