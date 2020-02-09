
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
    float worldViewWidth = worldViewHeight * aspectRatio;
    AABB bounds = {
        {
            floor(viewCenter.x - worldViewWidth / 2.0),
            ceil(viewCenter.x + worldViewWidth / 2.0)},
        {
            floor(viewCenter.y - worldViewHeight / 2.0),
            ceil(viewCenter.y + worldViewHeight / 2.0)}
    };
}

IVec2 getTileScreenPos(IVec2 tileWorldPos) {
    
}

SDL_Surface* MapRenderer::drawToSurface(Map* map) {
    AABB mapBounds = getVisibleBounds();
    SDL_Rect posRect = {0, 0, tileScreenSize, tileScreenSize};
    for (int x = mapBounds.topLeft.x; x <= mapBounds.bottomRight.x; x++) {
        for (int y = mapBounds.topLeft.y; y <= mapBounds.bottomRight.y; y++) {
            Sprite* sprite = map->getSpriteForPos({x, y});
            if (sprite == nullptr) {
                continue;
            }
            posRect.x = (x - mapBounds.topLeft.x) * tileScreenSize;
            posRect.y = (y - mapBounds.topLeft.y) * tileScreenSize;
            SDL_BlitScaled(
                sprite->getSurface(),
                NULL,
                surface,
                &posRect
            );
        }
    }
    return surface;
}
