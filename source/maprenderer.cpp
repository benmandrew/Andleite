
#include "maprenderer.h"

#include <iostream>

MapRenderer::MapRenderer() {
    screenLimits = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};
    aspectRatio = SCREEN_WIDTH / (float) SCREEN_HEIGHT;
    halfVerticalZoom = 12.5f;
    worldViewCenter = {10, 10};
    worldViewLimits = {halfVerticalZoom * aspectRatio, halfVerticalZoom};
    tileScreenSize = screenLimits.y / halfVerticalZoom;
    surface = SDL_CreateRGBSurface(
        0, screenLimits.x * 2, screenLimits.y * 2, 32, 0, 0, 0, 0);
}

MapRenderer::~MapRenderer() {
    delete surface;
}

AABB MapRenderer::getVisibleBounds() {
    AABB bounds = {
        {
            floor(worldViewCenter.x - worldViewLimits.x),
            floor(worldViewCenter.y - worldViewLimits.y)},
        {
            ceil(worldViewCenter.x + worldViewLimits.x),
            ceil(worldViewCenter.y + worldViewLimits.y)}
    };
    return bounds;
}

IVec2 MapRenderer::getTileScreenRect(IVec2 tileWorldPos, SDL_Rect* rect) {
    FVec2 normalisedWorldPoint = (tileWorldPos - worldViewCenter).toFloat() + worldViewLimits;
    IVec2 screenPoint = (normalisedWorldPoint * tileScreenSize).toInt();
    rect->x = screenPoint.x;
    rect->y = screenPoint.y;
    rect->w = tileScreenSize;
    rect->h = tileScreenSize;
}

Sprite* MapRenderer::getSpriteForTile(Tile* tile, SpriteIndex* spriteIndex) {
    Sprite* sprite;
    tile->updated = false;
    if (tile->visibility == TileVisibility::hidden) {
        sprite = spriteIndex->get(HIDDEN);
    } else if (tile->visibility == TileVisibility::seen) {
        if (tile->type == TileType::open) {
            sprite = spriteIndex->get(FLOOR_SEEN);
        } else {
            sprite = spriteIndex->get(WALL_SEEN);
        }
    } else {
        if (tile->type == TileType::open) {
            sprite = spriteIndex->get(FLOOR_VISIBLE);
        } else {
            sprite = spriteIndex->get(WALL_VISIBLE);
        }
    }
    return sprite;
}

void MapRenderer::drawMap(AABB* mapBounds, SDL_Rect* tileRect, Map* map, SpriteIndex* spriteIndex) {
    for (int x = (*mapBounds).topLeft.x; x <= (*mapBounds).bottomRight.x; x++) {
        for (int y = (*mapBounds).topLeft.y; y <= (*mapBounds).bottomRight.y; y++) {
            Tile* tile = map->getTile({x, y});
            if (tile == nullptr) continue;
            if (!tile->updated) continue;
            tile->updated = false;
            Sprite* sprite = getSpriteForTile(tile, spriteIndex);
            getTileScreenRect({x, y}, tileRect);
            SDL_BlitScaled(
                sprite->getSurface(),
                NULL,
                surface,
                tileRect
            );
        }
    }
}

void MapRenderer::drawEntity(Entity* entity, AABB* mapBounds, SDL_Rect* tileRect, SpriteIndex* spriteIndex) {
    if (!mapBounds->contains(entity->getPos())) return;
    getTileScreenRect(entity->getPos(), tileRect);
    SDL_BlitScaled(
        spriteIndex->get(
            entity->getSpriteEnum()
        )->getSurface(),
        NULL,
        surface,
        tileRect
    );
}

SDL_Surface* MapRenderer::drawToSurface(std::vector<Entity*> entities, Map* map, SpriteIndex* spriteIndex) {
    AABB mapBounds = getVisibleBounds();
    SDL_Rect tileRect = {0, 0, tileScreenSize, tileScreenSize};
    drawMap(&mapBounds, &tileRect, map, spriteIndex);
    for (Entity* entity : entities) {
        drawEntity(entity, &mapBounds, &tileRect, spriteIndex);
    }
    return surface;
}

void MapRenderer::setCameraPos(IVec2 pos) {
    worldViewCenter = pos;
}

void MapRenderer::setFocusedEntity(Entity* _focusedEntity) {
    focusedEntity = _focusedEntity;
}