#ifndef __MAP_H_INCLUDED__
#define __MAP_H_INCLUDED__

#pragma once

#include <random>
#include <time.h>
#include <SDL2/SDL.h>
#include "sprite.h"
#include "region.h"

enum Direction {
    north, east, south, west
};

class Map {
private:
    SDL_Rect mapPosRect;
    SDL_Surface* mapSurface;
    Tile grid[TILE_NUM_X][TILE_NUM_Y];
    std::vector<Region> regions;
    int nRegion;
    int regionTopID;

    Sprite* wallSprite;
    Sprite* openSprite;

    void generateMap();
    void initTiles();
    void generateRooms();
    void generateRoom(
        int x0, int y0, int x1, int y1);
    void generateCorridor(Vec2 pos);
    bool extendCorridor(Vec2* currentPos);
    void connectRegions();
    std::vector<Connector> getConnectors();

    bool adjacentToOpen(
        const Vec2 pos) const;
    bool adjacentToOpenInDirection(
        const Vec2 pos, const Vec2 offset,
        const Direction dir) const;
    bool getCandidateConnector(
        const Vec2 pos, std::pair<int, int>* regions) const;

public:
    void blitMap();
public:
    Map();
    ~Map();

    void init();
    void setTileType(const Vec2 pos, const TileType type);
    void setTileVisibility(
        const Vec2 pos, const TileVisibility visibility);
    Tile getTile(const Vec2 pos) const;
    SDL_Rect* getRect();
    SDL_Surface* getSurface() const;
};

#endif