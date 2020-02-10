#ifndef __MAPRENDERER_H_INCLUDED__
#define __MAPRENDERER_H_INCLUDED__
#pragma once

#include "map.h"
#include "fvec2.h"
#include "creature.h"

class MapRenderer {
    SDL_Surface* surface;
    IVec2 worldViewCenter; // Camera's position in the world
    FVec2 screenLimits; // Limits of the camera in screenspace
    float aspectRatio;
    float verticalZoom; // Number of visible tiles vertically
    FVec2 worldViewLimits; // Limits of the camera in worldspace
    float tileScreenSize; // Size of tile in screenspace

    AABB getVisibleBounds();
    IVec2 getTileScreenRect(IVec2 tileWorldPos, SDL_Rect* rect);
    Sprite* getSpriteForTile(Tile* tile, SpriteIndex* spriteIndex);
    void drawMap(AABB* mapBounds, SDL_Rect* tileRect, Map* map, SpriteIndex* spriteIndex);
    void drawEntity(Creature* entity, AABB* mapBounds, SDL_Rect* tileRect, SpriteIndex* spriteIndex);
public:
    MapRenderer();
    ~MapRenderer();
    SDL_Surface* drawToSurface(std::vector<Creature*> entities, Map* map, SpriteIndex* spriteIndex);
};

#endif