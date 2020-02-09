#ifndef __MAPRENDERER_H_INCLUDED__
#define __MAPRENDERER_H_INCLUDED__
#pragma once

#include "map.h"
#include "fvec2.h"

class MapRenderer {
    SDL_Surface* surface;
    IVec2 worldViewCenter;
    FVec2 screenLimits;
    float aspectRatio;
    float verticalZoom;
    FVec2 worldViewLimits;
    float tileScreenSize;

    AABB getVisibleBounds();
    IVec2 getTileScreenRect(IVec2 tileWorldPos, SDL_Rect* rect);
    Sprite* getSpriteForTile(Tile* tile, SpriteIndex* spriteIndex);
public:
    MapRenderer();
    ~MapRenderer();
    SDL_Surface* drawToSurface(Map* map, SpriteIndex* spriteIndex);
};

#endif