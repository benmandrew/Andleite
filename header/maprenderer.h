#ifndef __MAPRENDERER_H_INCLUDED__
#define __MAPRENDERER_H_INCLUDED__
#pragma once

#include "map.h"
#include "fvec2.h"
#include "entity.h"

class MapRenderer : public Observer {
    SDL_Surface* surface;
    IVec2 worldViewCenter; // Camera's position in the world
    FVec2 screenLimits; // Limits of the camera in screenspace
    float aspectRatio;
    float halfVerticalZoom; // Number of visible tiles vertically
    FVec2 worldViewLimits; // Limits of the camera in worldspace
    float tileScreenSize; // Size of tile in screenspace
    Entity* focusedEntity; // Whatever the camera is focused on

    AABB getVisibleBounds();
    IVec2 getTileScreenRect(IVec2 tileWorldPos, SDL_Rect* rect);
    Sprite* getSpriteForTile(Tile* tile, SpriteIndex* spriteIndex);
    void followFocusedEntity();
    void drawMap(AABB* mapBounds, SDL_Rect* tileRect, Map* map, SpriteIndex* spriteIndex);
    void drawEntity(Entity* entity, AABB* mapBounds, SDL_Rect* tileRect, SpriteIndex* spriteIndex);
public:
    MapRenderer();
    ~MapRenderer();
    SDL_Surface* drawToSurface(std::vector<Entity*> entities, Map* map, SpriteIndex* spriteIndex);
    void setCameraPos(IVec2 pos);
    void setFocusedEntity(Entity* _focusedEntity);
    void onNotify(int event);
};

#endif