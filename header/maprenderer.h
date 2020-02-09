#ifndef __MAPRENDERER_H_INCLUDED__
#define __MAPRENDERER_H_INCLUDED__
#pragma once

#include "map.h"

class MapRenderer {
    SDL_Surface* surface;
    Vec2 viewCenter, viewCorner;
public:
    MapRenderer(AABB _bounds);
    ~MapRenderer();
    SDL_Surface* drawToSurface(Map* map);
};

#endif