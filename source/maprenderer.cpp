
#include "maprenderer.h"

MapRenderer::MapRenderer() {
    surface = new SDL_Surface();
    viewCenter = {0, 0};
    viewLimits = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};
    worldViewHeight = 25.0f;
}

MapRenderer::~MapRenderer() {
    delete surface;
}

AABB MapRenderer::getVisibleBounds() {
    AABB bounds = {
        {
            floor(worldViewCenter.x - worldViewLimits.x / 2.0),
            ceil(worldViewCenter.x + worldViewLimits.x / 2.0)},
        {
            floor(worldViewCenter.y - worldViewLimits.y / 2.0),
            ceil(worldViewCenter.y + worldViewLimits.y / 2.0)}
    };
}

IVec2 MapRenderer::getTileScreenRect(IVec2 tileWorldPos, SDL_Rect* rect) {
    FVec2 normalisedWorldPoint = (tileWorldPos - worldViewCenter).toFloat() + worldViewLimits;
    IVec2 screenPoint = (normalisedWorldPoint * tileScreenSize).toInt();
    rect->x = screenPoint.x;
    rect->y = screenPoint.y;
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

SDL_Surface* MapRenderer::drawToSurface(Map* map, SpriteIndex* spriteIndex) {
    AABB mapBounds = getVisibleBounds();
    SDL_Rect tileRect = {0, 0, tileScreenSize, tileScreenSize};
    for (int x = mapBounds.topLeft.x; x <= mapBounds.bottomRight.x; x++) {
        for (int y = mapBounds.topLeft.y; y <= mapBounds.bottomRight.y; y++) {
            Tile* tile = map->getTile({x, y});
            if (tile == nullptr) continue;
            if (!tile->updated) continue;
            Sprite* sprite = getSpriteForTile(tile, spriteIndex);
            getTileScreenRect({x, y}, &tileRect);
            SDL_BlitScaled(
                sprite->getSurface(),
                NULL,
                surface,
                &tileRect
            );
        }
    }
    return surface;
}
