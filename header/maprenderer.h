#ifndef __MAPRENDERER_H_INCLUDED__
#define __MAPRENDERER_H_INCLUDED__
#pragma once

#include "map.h"
#include "fvec2.h"

class MapRenderer {
    SDL_Surface* surface;
    IVec2 viewCenter;
    FVec2 viewLimits;
    float aspectRatio;
    float worldViewHeight;
    float tileScreenSize;

    AABB getVisibleBounds();
    IVec2 getTileScreenPos(IVec2 tileWorldPos);
public:
    MapRenderer();
    ~MapRenderer();
    SDL_Surface* drawToSurface(Map* map);
};

#endif