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
    Tile grid[TILE_NUM_X][TILE_NUM_Y];
    std::vector<Region> regions;
    int nRegion;
    int regionTopID;

    void generateMap();
    void initTiles();
    void generateRooms();
    void generateRoom(
        int x0, int y0, int x1, int y1);
    void generateCorridor(IVec2 pos);
    bool extendCorridor(IVec2* currentPos);
    void connectRegions();
    std::vector<Connector> getConnectors();

    bool adjacentToOpen(
        const IVec2 pos) const;
    bool adjacentToOpenInDirection(
        const IVec2 pos, const IVec2 offset,
        const Direction dir) const;
    bool getCandidateConnector(
        const IVec2 pos, std::pair<int, int>* regions) const;
    Sprite* getSpriteForTile(Tile* tile);

public:
    Map();
    ~Map();

    void blitMap();
    void visibleToSeen();
    void init();
    void setTileType(const IVec2 pos, const TileType type);
    void setTileVisibility(
        const IVec2 pos, const TileVisibility visibility);
    Tile getTile(const IVec2 pos) const;
};

#endif